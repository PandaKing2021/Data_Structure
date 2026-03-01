/**
 * Block Search (Indexed Sequential Search) Header
 *
 * Block search is an improved version of sequential search that divides
 * the sorted array into blocks and uses an index table to quickly locate
 * the appropriate block before searching within it.
 *
 * Algorithm:
 * 1. Search index table to find the block containing the key
 * 2. Perform sequential search within that block
 *
 * Performance:
 * - Time Complexity: O(√n) with optimal block size √n
 * - Space Complexity: O(√n) for the index table
 * - Best for: Large sorted datasets where sequential search is too slow
 *
 * Optimal Block Size:
 * For an array of size n, the optimal block size is √n, which balances
 * the cost of searching the index and searching within a block.
 *
 * Variants:
 * - Sequential search on index: Simpler, O(√n)
 * - Binary search on index: Faster for many blocks, O(log √n + √n)
 */

#ifndef BLOCK_SEARCH_H
#define BLOCK_SEARCH_H

/**
 * Maximum block size supported
 */
#define MAX_BLOCK_SIZE 100

/**
 * Index Block Structure
 * Represents one block in the indexed search table
 */
typedef struct {
    int key;        // Maximum key value in this block
    int start;      // Starting index of this block in the array
    int end;        // Ending index of this block in the array
} IndexBlock;

/**
 * Block search using sequential search on index
 * First finds the appropriate block by searching the index table,
 * then performs sequential search within that block.
 *
 * @param arr Sorted array to search
 * @param n Number of elements in array
 * @param index Index table for blocks
 * @param blockNum Number of blocks
 * @param key Key to search for
 * @return Index of key if found, -1 if not found
 */
int BlockSearch(int arr[], int n, IndexBlock index[], int blockNum, int key);

/**
 * Create index table for block search
 * Divides the sorted array into blocks of specified size
 * and records the maximum key and start/end positions for each block.
 *
 * @param arr Sorted array
 * @param n Number of elements in array
 * @param blockSize Size of each block
 * @param index Output index table
 * @return Number of blocks created
 */
int CreateIndexTable(int arr[], int n, int blockSize, IndexBlock index[]);

/**
 * Block search using binary search on index
 * First uses binary search on the index table to find the block,
 * then performs sequential search within that block.
 * More efficient than sequential index search for large datasets.
 *
 * @param arr Sorted array to search
 * @param n Number of elements in array
 * @param index Index table for blocks
 * @param blockNum Number of blocks
 * @param key Key to search for
 * @return Index of key if found, -1 if not found
 */
int BlockSearchWithBinary(int arr[], int n, IndexBlock index[], int blockNum, int key);

#endif
