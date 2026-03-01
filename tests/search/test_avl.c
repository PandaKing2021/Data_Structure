#include <stdio.h>
#include "include/search/avl_tree.h"

int main() {
    printf("=== AVL Tree Test ===\n");

    AVLNode *root = NULL;

    printf("Insert: 10, 20, 30, 40, 50, 25\n");
    root = AVL_Insert(root, 10);
    root = AVL_Insert(root, 20);
    root = AVL_Insert(root, 30);
    root = AVL_Insert(root, 40);
    root = AVL_Insert(root, 50);
    root = AVL_Insert(root, 25);

    printf("InOrder traversal: ");
    AVL_InOrder(root);
    printf("\n");

    printf("Tree root: %d (balance factor: %d)\n",
           root->key, GetBalance(root));

    printf("Delete 30\n");
    root = AVL_Delete(root, 30);
    printf("InOrder traversal after deletion: ");
    AVL_InOrder(root);
    printf("\n");

    return 0;
}
