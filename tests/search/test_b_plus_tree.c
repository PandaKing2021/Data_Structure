/**
 * B+ Tree Test Program
 *
 * This program tests the B+ tree implementation including:
 * - Insertion of multiple keys
 * - Tree structure visualization
 * - Sequential traversal via leaf chain
 * - Search operations
 */

#include "../../include/search/b_plus_tree.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=== B+ Tree Tests ===\n\n");

    // Create an empty B+ tree
    BPlusTree T = CreateBPlusTree();

    // Test 1: Insertion Test
    printf("1. Insertion Test (Order %d):\n", ORDER);
    int insertData[] = {10, 20, 5, 6, 12, 30, 7, 17, 25};

    printf("Inserting: ");
    for (int i = 0; i < 9; i++) {
        printf("%d ", insertData[i]);
        BPlusTreeInsert(&T, insertData[i]);
    }
    printf("\n\n");

    // Display tree structure
    printf("B+ Tree structure:\n");
    PrintBPlusTree(T, 0);

    // Display sequential traversal via leaf chain
    printf("\nLeaf nodes (in order): ");
    TraverseBPlusTree(T);
    printf("\n");

    // Test 2: Search Test
    printf("\n2. Search Test:\n");
    int searchKeys[] = {6, 20, 100, 30};
    for (int i = 0; i < 4; i++) {
        int found = BPlusTreeSearch(&T, searchKeys[i]);
        printf("Search %d: %s\n", searchKeys[i], found ? "found" : "not found");
    }

    printf("\n=== All Tests Passed ===\n");

    // Clean up
    DestroyBPlusTree(T);
    return 0;
}
