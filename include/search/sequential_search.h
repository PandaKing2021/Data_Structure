/**
 * Sequential Search Header
 *
 * Sequential (linear) search is the simplest search algorithm that checks
 * each element of an array one by one until the target is found or the
 * end is reached.
 *
 * Algorithm:
 * - Start from the first element
 * - Compare each element with the target
 * - Return index when found, or -1 if not found
 *
 * Performance:
 * - Time Complexity: O(n) worst case, O(1) best case
 * - Space Complexity: O(1) - no extra space needed
 * - Average comparisons: n/2
 *
 * Variants:
 * 1. Standard Sequential Search: Basic implementation
 * 2. Sentinel Search: Optimization to reduce comparisons
 * 3. Comparison Counting: For algorithm analysis
 *
 * Best Use Cases:
 * - Small datasets (n < 20)
 * - Unsorted data
 * - When simplicity is more important than speed
 * - When sorting cost outweighs search cost
 */

#ifndef SEQUENTIAL_SEARCH_H
#define SEQUENTIAL_SEARCH_H

/**
 * Standard sequential search
 * Iterates through array and compares each element with the key.
 *
 * @param arr Array to search
 * @param n Number of elements in array
 * @param key Value to search for
 * @return Index of key if found, -1 if not found
 */
int SequentialSearch(int arr[], int n, int key);

/**
 * Sequential search with sentinel optimization
 * Places the key at position 0 (sentinel) to eliminate boundary checking
 * in the loop. Data is stored in arr[1..n], arr[0] is used as sentinel.
 *
 * Advantages:
 * - Reduces number of comparisons (no need to check i < n)
 * - Slight performance improvement
 *
 * @param arr Array with sentinel at position 0, data at 1..n
 * @param n Number of valid elements (excluding sentinel)
 * @param key Value to search for
 * @return Index of key if found, 0 if not found (sentinel position)
 */
int SentinelSearch(int arr[], int n, int key);

/**
 * Sequential search with comparison counting
 * Returns the number of comparisons performed during the search.
 * Useful for analyzing algorithm performance and comparing search methods.
 *
 * @param arr Array to search
 * @param n Number of elements in array
 * @param key Value to search for
 * @return Number of comparisons made
 */
int SequentialSearchCount(int arr[], int n, int key);

#endif
