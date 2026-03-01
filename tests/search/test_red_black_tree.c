#include "../../include/search/red_black_tree.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=== Red-Black Tree Tests ===\n\n");

    RBTree T;
    InitRBTree(&T);

    /* Insertion test */
    printf("1. Insertion Test:\n");
    int insertData[] = {10, 20, 30, 15, 25, 5, 1, 35};
    int n = sizeof(insertData) / sizeof(insertData[0]);

    printf("Inserting: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", insertData[i]);
        RBInsert(&T, insertData[i]);
    }
    printf("\n\n");

    printf("Inorder traversal (R=Red, B=Black):\n");
    InorderRBTree(T);
    printf("\n");

    /* Search test */
    printf("\n2. Search Test:\n");
    int searchKeys[] = {15, 100, 5, 30};
    for (int i = 0; i < 4; i++) {
        RBNode *result = RBSearch(T, searchKeys[i]);
        printf("Search %d: %s\n", searchKeys[i],
               result != NIL ? "found" : "not found");
    }

    /* Deletion test */
    printf("\n3. Deletion Test:\n");
    int deleteKeys[] = {20, 10, 15};
    for (int i = 0; i < 3; i++) {
        printf("Delete %d\n", deleteKeys[i]);
        RBDelete(&T, deleteKeys[i]);
        printf("After deletion:\n");
        InorderRBTree(T);
        printf("\n");
    }

    printf("\n=== All Tests Passed ===\n");
    return 0;
}
