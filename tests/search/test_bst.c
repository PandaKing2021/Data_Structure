#include <stdio.h>
#include "include/search/binary_search_tree.h"

int main() {
    printf("=== Binary Search Tree Test ===\n");

    BSTNode *T = NULL;

    printf("Insert: 50, 30, 70, 20, 40, 60, 80\n");
    T = BST_Insert(T, 50);
    T = BST_Insert(T, 30);
    T = BST_Insert(T, 70);
    T = BST_Insert(T, 20);
    T = BST_Insert(T, 40);
    T = BST_Insert(T, 60);
    T = BST_Insert(T, 80);

    printf("InOrder traversal: ");
    BST_InOrder(T);
    printf("\n");

    int key = 40;
    BSTNode *result = BST_Search(T, key);
    printf("Search %d: %s\n", key, result ? "Found" : "Not found");

    printf("Delete 30\n");
    T = BST_Delete(T, 30);
    printf("InOrder traversal after deletion: ");
    BST_InOrder(T);
    printf("\n");

    return 0;
}
