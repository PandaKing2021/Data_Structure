/**
 * Sequential Search Implementation
 *
 * Sequential search is the simplest searching algorithm that checks each
 * element one by one until the target is found or the end is reached.
 *
 * Time Complexity: O(n) - must check all elements in worst case
 * Space Complexity: O(1) - no extra space needed
 *
 * Variants:
 * - Standard sequential search
 * - Sentinel search (optimization to reduce comparisons)
 * - Comparison count (for analysis)
 */

#include "../../include/search/sequential_search.h"
#include <stdio.h>

/**
 * Standard sequential search
 * Iterates through array and compares each element with the key
 *
 * @param arr Array to search in
 * @param n Number of elements in array
 * @param key Value to search for
 * @return Index of key if found, -1 if not found
 */
int SequentialSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            return i;  // Key found
        }
    }
    return -1;  // Key not found
}

/**
 * Sequential search with sentinel optimization
 * Uses arr[0] as a sentinel to avoid boundary checking in loop
 * Data is stored in arr[1..n]
 *
 * Advantages:
 * - Reduces number of comparisons (no need to check i < n)
 * - Slight performance improvement
 *
 * @param arr Array to search in (arr[0] is sentinel, arr[1..n] is data)
 * @param n Number of elements (excluding sentinel)
 * @param key Value to search for
 * @return Index of key if found, 0 if not found (sentinel position)
 */
int SentinelSearch(int arr[], int n, int key) {
    arr[0] = key;  // Place key at sentinel position
    int i = n;

    // No need to check i > 0 - sentinel guarantees termination
    while (arr[i] != key) {
        i--;
    }

    return i;  // 0 means not found (reached sentinel)
}

/**
 * Sequential search with comparison counting
 * Returns the number of comparisons performed
 * Useful for analyzing search algorithm performance
 *
 * @param arr Array to search in
 * @param n Number of elements in array
 * @param key Value to search for
 * @return Number of comparisons made
 */
int SequentialSearchCount(int arr[], int n, int key) {
    int count = 0;

    for (int i = 0; i < n; i++) {
        count++;  // Count this comparison
        if (arr[i] == key) {
            return count;  // Found, return comparison count
        }
    }

    return count;  // Not found, return total comparisons
}
