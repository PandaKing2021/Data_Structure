#include "../../include/search/block_search.h"
#include <stdio.h>

int main() {
    printf("=== Block Search Tests ===\n\n");

    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    int n = sizeof(arr) / sizeof(arr[0]);
    int blockSize = 5;

    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%2d ", arr[i]);
    }
    printf("\n");

    /* Create index table */
    IndexBlock index[100];
    int blockNum = CreateIndexTable(arr, n, blockSize, index);

    printf("\nIndex Table:\n");
    for (int i = 0; i < blockNum; i++) {
        printf("Block %d: max=%d, range=[%d, %d]\n",
               i, index[i].key, index[i].start, index[i].end);
    }

    /* Block search */
    printf("\nBlock Search:\n");
    int keys[] = {7, 17, 22, 30};

    for (int i = 0; i < 4; i++) {
        int result = BlockSearch(arr, n, index, blockNum, keys[i]);
        printf("Search %2d: %s\n", keys[i],
               result != -1 ? "found" : "not found");
        if (result != -1) {
            printf("  Found at index %d\n", result);
        }
    }

    /* Block search with binary */
    printf("\nBlock Search with Binary:\n");
    for (int i = 0; i < 4; i++) {
        int result = BlockSearchWithBinary(arr, n, index, blockNum, keys[i]);
        printf("Search %2d: %s\n", keys[i],
               result != -1 ? "found" : "not found");
        if (result != -1) {
            printf("  Found at index %d\n", result);
        }
    }

    printf("\n=== All Tests Passed ===\n");
    return 0;
}
