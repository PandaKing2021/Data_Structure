/**
 * External Sort Header File
 *
 * External sort handles sorting of data that doesn't fit in memory.
 * Uses a two-phase approach with run generation and k-way merging.
 *
 * Phase 1: Sort chunks in memory -> write to temporary run files
 * Phase 2: Merge sorted runs -> write to final output
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(M) where M is memory buffer size
 */

#ifndef EXTERNAL_SORT_H
#define EXTERNAL_SORT_H

#include <stdio.h>

/**
 * Size of each sorted run (number of elements)
 */
#define RUN_SIZE 1000

/**
 * Memory buffer size for reading/writing chunks
 */
#define MEMORY_BUFFER 1000

/**
 * Maximum number of concurrent runs during merge phase
 */
#define MAX_RUNS 100

/**
 * Run File Structure
 * Represents a sorted run file with its buffer
 */
typedef struct {
    FILE *file;                      // File pointer to run file
    int buffer[MEMORY_BUFFER];        // Input buffer for the run
    int current;                     // Current read position in buffer
    int valid;                       // Number of valid elements in buffer
} RunFile;

/**
 * Loser Tree Node Structure
 * Used in k-way merging to efficiently track minimum values
 */
typedef struct {
    int key;                         // Key value for comparison
    int runIndex;                    // Index of the run this value comes from
    int value;                       // Actual value
} LoserTreeNode;

/**
 * Main external sort function
 * Orchestrates run generation and merging
 *
 * @param inputFile Path to input file
 * @param outputFile Path to output file
 */
void ExternalSort(const char *inputFile, const char *outputFile);

/**
 * Create initial sorted runs
 * Reads input file in chunks, sorts each chunk, writes to run files
 *
 * @param inputFile Path to input file
 * @return Number of runs created, or -1 on error
 */
int CreateRuns(const char *inputFile);

/**
 * Merge all sorted runs into single output
 * Opens all run files and performs k-way merge
 *
 * @param outputFile Path to output file
 * @param runCount Number of runs to merge
 */
void MergeRuns(const char *outputFile, int runCount);

/**
 * K-way merge using simple method
 * Repeatedly selects minimum from all active runs
 *
 * @param runs Array of run structures
 * @param k Number of runs to merge
 * @param output Output file pointer
 */
void KWayMerge(RunFile runs[], int k, FILE *output);

/**
 * K-way merge using loser tree
 * More efficient for large number of runs
 *
 * @param runs Array of run structures
 * @param k Number of runs to merge
 * @param output Output file pointer
 */
void LoserTreeMerge(RunFile runs[], int k, FILE *output);

/**
 * Build loser tree for k-way merging
 * Loser tree tracks which run has the minimum value
 *
 * @param tree Loser tree array
 * @param runs Array of run structures
 * @param k Number of runs
 * @return Index of run with minimum value
 */
int BuildLoserTree(LoserTreeNode tree[], RunFile runs[], int k);

/**
 * Quick sort for in-memory sorting
 * Used to sort chunks during run generation
 *
 * @param arr Array to sort
 * @param low Starting index
 * @param high Ending index
 */
void QuickSortExternal(int arr[], int low, int high);

/**
 * Partition function for quick sort
 * Selects pivot and partitions array
 *
 * @param arr Array to partition
 * @param low Starting index
 * @param high Ending index
 * @return Final position of pivot
 */
int PartitionExternal(int arr[], int low, int high);

#endif
