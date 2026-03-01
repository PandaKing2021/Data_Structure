/**
 * Block Search (Indexed Sequential Search) Implementation
 *
 * Block search is an improved version of sequential search that uses
 * an index table to divide the data into blocks. First searches the
 * index to find the correct block, then searches within that block.
 *
 * Time Complexity: O(√n) with optimal block size
 * Space Complexity: O(√n) for the index table
 *
 * Optimal block size: √n for balanced performance
 *
 * Variants:
 * - Sequential search on index
 * - Binary search on index (faster for large datasets)
 */

#include "../../include/search/block_search.h"
#include <stdio.h>

/**
 * Create an index table for block search
 * Divides the array into blocks and records the maximum key
 * and start/end position for each block
 *
 * @param arr Array to create index for
 * @param n Number of elements in array
 * @param blockSize Size of each block
 * @param index Output index table
 * @return Number of blocks created
 */
int CreateIndexTable(int arr[], int n, int blockSize, IndexBlock index[]) {
    int blockNum = 0;
    int i = 0;

    while (i < n) {
        int start = i;
        int maxKey = arr[i];

        // Find maximum key in this block
        int j;
        for (j = i; j < i + blockSize && j < n; j++) {
            if (arr[j] > maxKey) {
                maxKey = arr[j];
            }
        }

        // Store block information in index
        index[blockNum].key = maxKey;
        index[blockNum].start = start;
        index[blockNum].end = j - 1;

        blockNum++;
        i = j;  // Move to next block
    }

    return blockNum;
}

/**
 * Block search using sequential search on index
 *
 * Process:
 * 1. Search index table sequentially to find appropriate block
 * 2. Search within the identified block sequentially
 *
 * @param arr Array to search in
 * @param n Number of elements
 * @param index Index table
 * @param blockNum Number of blocks in index
 * @param key Value to search for
 * @return Index of key if found, -1 if not found
 */
int BlockSearch(int arr[], int n, IndexBlock index[], int blockNum, int key) {
    // Step 1: Search index table sequentially for appropriate block
    int blockIndex = -1;
    for (int i = 0; i < blockNum; i++) {
        if (key <= index[i].key) {
            blockIndex = i;
            break;
        }
    }

    if (blockIndex == -1) {
        return -1;  // Key not in any block
    }

    // Step 2: Search within the identified block
    int start = index[blockIndex].start;
    int end = index[blockIndex].end;

    for (int i = start; i <= end; i++) {
        if (arr[i] == key) {
            return i;  // Key found
        }
    }

    return -1;  // Key not found in block
}

/**
 * Block search using binary search on index
 *
 * Process:
 * 1. Search index table using binary search to find appropriate block
 * 2. Search within the identified block sequentially
 *
 * More efficient than sequential index search for large datasets
 *
 * @param arr Array to search in
 * @param n Number of elements
 * @param index Index table
 * @param blockNum Number of blocks in index
 * @param key Value to search for
 * @return Index of key if found, -1 if not found
 */
int BlockSearchWithBinary(int arr[], int n, IndexBlock index[], int blockNum, int key) {
    // Step 1: Binary search on index table
    int left = 0, right = blockNum - 1;
    int blockIndex = -1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (key <= index[mid].key) {
            // Check if this is the correct block
            if (mid == 0 || key > index[mid - 1].key) {
                blockIndex = mid;
                break;
            }
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if (blockIndex == -1) {
        return -1;  // Key not in any block
    }

    // Step 2: Search within the identified block
    int start = index[blockIndex].start;
    int end = index[blockIndex].end;

    for (int i = start; i <= end; i++) {
        if (arr[i] == key) {
            return i;  // Key found
        }
    }

    return -1;  // Key not found in block
}
