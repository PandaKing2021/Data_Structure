#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

typedef struct BSTNode {
    int key;
    struct BSTNode *lchild, *rchild;
} BSTNode;

BSTNode *BST_Insert(BSTNode *T, int key);
BSTNode *BST_Search(BSTNode *T, int key);
BSTNode *BST_Delete(BSTNode *T, int key);
void BST_InOrder(BSTNode *T);

#endif
