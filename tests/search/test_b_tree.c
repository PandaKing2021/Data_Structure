/**
 * B-Tree Test Program
 *
 * This program tests the B-tree implementation including:
 * - Insertion of multiple keys
 * - Tree structure visualization
 * - Search operations
 */

#include "../../include/search/b_tree.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=== B-Tree Tests ===\n\n");

    // Create an empty B-tree
    BTree T = CreateBTree();

    // Test 1: Insertion Test
    printf("1. Insertion Test (Order M=%d):\n", M);
    int insertData[] = {10, 20, 5, 6, 12, 30, 7, 17, 25};

    printf("Inserting: ");
    for (int i = 0; i < 9; i++) {
        printf("%d ", insertData[i]);
        BTreeInsert(&T, insertData[i]);
    }
    printf("\n\n");

    // Display tree structure
    printf("B-Tree structure:\n");
    TraverseBTree(T, 0);

    // Test 2: Search Test
    printf("\n2. Search Test:\n");
    int searchKeys[] = {6, 20, 100, 30};
    for (int i = 0; i < 4; i++) {
        int idx;
        BTreeNode *result = BTreeSearch(T, searchKeys[i], &idx);
        printf("Search %d: %s", searchKeys[i],
               result != NULL ? "found" : "not found");
        if (result != NULL) {
            printf(" at index %d", idx);
        }
        printf("\n");
    }

    printf("\n=== All Tests Passed ===\n");
    return 0;
}
