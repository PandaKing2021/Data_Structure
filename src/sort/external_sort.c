/**
 * External Sort Implementation
 *
 * External sort is used when data is too large to fit in memory.
 * It uses a two-phase approach:
 * Phase 1: Sort chunks in memory and write to temporary files (runs)
 * Phase 2: Merge sorted runs using k-way merge algorithm
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(M) where M is memory buffer size
 *
 * This implementation uses:
 * - Quick sort for in-memory sorting
 * - K-way merge for combining sorted runs
 * - Buffering to minimize disk I/O
 */

#include "../../include/sort/external_sort.h"
#include <stdlib.h>
#include <string.h>

/**
 * Partition function for quick sort
 * Selects last element as pivot and partitions the array
 *
 * @param arr Array to partition
 * @param low Starting index
 * @param high Ending index
 * @return Final position of pivot
 */
int PartitionExternal(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

/**
 * Quick sort implementation for external sorting
 * Sorts array in place using divide and conquer
 *
 * @param arr Array to sort
 * @param low Starting index
 * @param high Ending index
 */
void QuickSortExternal(int arr[], int low, int high) {
    if (low < high) {
        int pi = PartitionExternal(arr, low, high);
        QuickSortExternal(arr, low, pi - 1);
        QuickSortExternal(arr, pi + 1, high);
    }
}

/**
 * Phase 1: Create initial sorted runs
 * Reads data from input file, sorts chunks in memory,
 * and writes them to temporary run files
 *
 * @param inputFile Path to input file
 * @return Number of runs created, or -1 on error
 */
int CreateRuns(const char *inputFile) {
    FILE *input = fopen(inputFile, "r");
    if (!input) {
        printf("Cannot open input file: %s\n", inputFile);
        return -1;
    }

    int runCount = 0;
    int buffer[MEMORY_BUFFER];
    int count;

    // Read file in chunks, sort each chunk, write to run file
    while ((count = fread(buffer, sizeof(int), MEMORY_BUFFER, input)) > 0) {
        QuickSortExternal(buffer, 0, count - 1);

        char filename[100];
        sprintf(filename, "run_%d.tmp", runCount);
        FILE *runFile = fopen(filename, "w");
        if (!runFile) {
            printf("Cannot create run file: %s\n", filename);
            fclose(input);
            return -1;
        }

        fwrite(buffer, sizeof(int), count, runFile);
        fclose(runFile);

        runCount++;
    }

    fclose(input);
    return runCount;
}

/**
 * Build loser tree for k-way merging
 * Loser tree is a tournament tree that keeps track of minimum
 * values from multiple sorted runs
 *
 * @param tree Loser tree structure
 * @param runs Array of run files
 * @param k Number of runs
 * @return Index of run with minimum value
 */
int BuildLoserTree(LoserTreeNode tree[], RunFile runs[], int k) {
    // Initialize leaf nodes
    for (int i = 0; i < k; i++) {
        tree[k + i].key = runs[i].buffer[runs[i].current];
        tree[k + i].runIndex = i;
        tree[k + i].value = runs[i].buffer[runs[i].current];
    }

    // Initialize losers
    for (int i = 0; i < k; i++) {
        int parent = (k + i) / 2;
        int child = k + i;

        while (parent >= 1) {
            int sibling = (parent * 2 == child) ? child + 1 : child - 1;

            if (tree[child].key < tree[sibling].key) {
                tree[parent] = tree[sibling];
                child = parent;
                parent = child / 2;
            } else {
                tree[parent] = tree[child];
                parent = parent / 2;
            }
        }
    }

    return tree[1].runIndex;
}

/**
 * K-way merge using simple method
 * Repeatedly selects minimum from all active runs
 *
 * @param runs Array of run files
 * @param k Number of runs
 * @param output Output file
 */
void KWayMerge(RunFile runs[], int k, FILE *output) {
    int activeRuns = k;

    while (activeRuns > 0) {
        int minValue = 2147483647;
        int minIndex = -1;

        // Find minimum among all active runs
        for (int i = 0; i < k; i++) {
            if (runs[i].valid && runs[i].current < MEMORY_BUFFER) {
                if (runs[i].buffer[runs[i].current] < minValue) {
                    minValue = runs[i].buffer[runs[i].current];
                    minIndex = i;
                }
            }
        }

        if (minIndex != -1) {
            fwrite(&minValue, sizeof(int), 1, output);

            runs[minIndex].current++;
            // Read next chunk if buffer exhausted
            if (runs[minIndex].current >= MEMORY_BUFFER ||
                runs[minIndex].current >= runs[minIndex].valid) {
                runs[minIndex].valid = fread(runs[minIndex].buffer,
                                          sizeof(int),
                                          MEMORY_BUFFER,
                                          runs[minIndex].file);
                runs[minIndex].current = 0;

                if (runs[minIndex].valid <= 0) {
                    runs[minIndex].valid = 0;
                    activeRuns--;
                }
            }
        }
    }
}

/**
 * K-way merge using loser tree
 * More efficient than simple K-way merge for large k
 *
 * @param runs Array of run files
 * @param k Number of runs
 * @param output Output file
 */
void LoserTreeMerge(RunFile runs[], int k, FILE *output) {
    LoserTreeNode tree[2 * k];

    // Initialize all buffers
    for (int i = 0; i < k; i++) {
        runs[i].valid = fread(runs[i].buffer, sizeof(int), MEMORY_BUFFER, runs[i].file);
        runs[i].current = 0;
    }

    while (1) {
        // Check if any data remains
        int hasData = 0;
        for (int i = 0; i < k; i++) {
            if (runs[i].valid && runs[i].current < runs[i].valid) {
                hasData = 1;
                break;
            }
        }

        if (!hasData) {
            break;
        }

        // Get minimum value using loser tree
        int minIndex = BuildLoserTree(tree, runs, k);

        if (minIndex == -1) {
            break;
        }

        // Output minimum value
        fwrite(&runs[minIndex].buffer[runs[minIndex].current], sizeof(int), 1, output);

        // Read next value from corresponding run
        runs[minIndex].current++;

        if (runs[minIndex].current >= runs[minIndex].valid) {
            runs[minIndex].valid = fread(runs[minIndex].buffer,
                                      sizeof(int),
                                      MEMORY_BUFFER,
                                      runs[minIndex].file);
            runs[minIndex].current = 0;
        }
    }
}

/**
 * Phase 2: Merge all sorted runs
 * Opens all run files and merges them into single output file
 *
 * @param outputFile Path to output file
 * @param runCount Number of runs to merge
 */
void MergeRuns(const char *outputFile, int runCount) {
    FILE *output = fopen(outputFile, "w");
    if (!output) {
        printf("Cannot create output file: %s\n", outputFile);
        return;
    }

    RunFile runs[MAX_RUNS];

    // Open all run files
    for (int i = 0; i < runCount; i++) {
        char filename[100];
        sprintf(filename, "run_%d.tmp", i);

        runs[i].file = fopen(filename, "r");
        if (!runs[i].file) {
            printf("Cannot open run file: %s\n", filename);
            for (int j = 0; j < i; j++) {
                fclose(runs[j].file);
            }
            fclose(output);
            return;
        }

        runs[i].current = 0;
        runs[i].valid = 0;
    }

    // Use K-way merge
    KWayMerge(runs, runCount, output);

    // Close all files and cleanup
    for (int i = 0; i < runCount; i++) {
        fclose(runs[i].file);

        char filename[100];
        sprintf(filename, "run_%d.tmp", i);
        remove(filename);
    }

    fclose(output);
    printf("Merged %d runs into %s\n", runCount, outputFile);
}

/**
 * External sort main function
 * Orchestrates the two-phase external sorting process
 *
 * Phase 1: Create initial sorted runs from input file
 * Phase 2: Merge all runs into final sorted output
 *
 * @param inputFile Path to input file
 * @param outputFile Path to output file
 */
void ExternalSort(const char *inputFile, const char *outputFile) {
    printf("External Sort: %s -> %s\n", inputFile, outputFile);

    // Phase 1: Create initial runs
    printf("Phase 1: Creating initial runs...\n");
    int runCount = CreateRuns(inputFile);

    if (runCount <= 0) {
        printf("No data to sort or error occurred.\n");
        return;
    }

    printf("Created %d initial runs\n", runCount);

    // Phase 2: Merge all runs
    printf("Phase 2: Merging runs...\n");
    MergeRuns(outputFile, runCount);

    printf("External sort completed!\n");
}
