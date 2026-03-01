#include <stdio.h>
#include "include/tree/binary_tree.h"

int main() {
    printf("=== Binary Tree Test ===\n");
    printf("Create binary tree (enter -1 for null node):\n");
    printf("Example tree: 1 2 4 -1 -1 5 -1 -1 3 -1 -1\n");

    BTNode *T;
    CreateBTree(&T);

    printf("\nPreOrder traversal: ");
    PreOrder(T);

    printf("\nInOrder traversal: ");
    InOrder(T);

    printf("\nPostOrder traversal: ");
    PostOrder(T);

    printf("\nLevelOrder traversal: ");
    LevelOrder(T);

    printf("\nTree depth: %d\n", TreeDepth(T));
    printf("Node count: %d\n", NodeCount(T));
    printf("Leaf count: %d\n", LeafCount(T));

    return 0;
}
