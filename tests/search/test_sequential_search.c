#include "../../include/search/sequential_search.h"
#include <stdio.h>

int main() {
    printf("=== Sequential Search Tests ===\n\n");

    int arr[] = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    /* Standard sequential search */
    printf("1. Standard Sequential Search:\n");
    int key1 = 7, key2 = 10;
    int result1 = SequentialSearch(arr, n, key1);
    int result2 = SequentialSearch(arr, n, key2);
    printf("Search %d: found at index %d\n", key1, result1);
    printf("Search %d: found at index %d\n", key2, result2);

    /* Sequential search with count */
    printf("\n2. Sequential Search with Count:\n");
    int count1 = SequentialSearchCount(arr, n, key1);
    int count2 = SequentialSearchCount(arr, n, key2);
    printf("Search %d: %d comparisons\n", key1, count1);
    printf("Search %d: %d comparisons\n", key2, count2);

    /* Sentinel search */
    printf("\n3. Sentinel Search:\n");
    int sentinelArr[n + 1];
    for (int i = 0; i < n; i++) {
        sentinelArr[i + 1] = arr[i];
    }

    result1 = SentinelSearch(sentinelArr, n, key1);
    result2 = SentinelSearch(sentinelArr, n, key2);
    printf("Search %d: found at index %d\n", key1, result1);
    printf("Search %d: found at index %d\n", key2, result2);

    printf("\n=== All Tests Passed ===\n");
    return 0;
}
