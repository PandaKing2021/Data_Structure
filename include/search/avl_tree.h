#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct AVLNode {
    int key;
    int height;
    struct AVLNode *lchild, *rchild;
} AVLNode;

int Height(AVLNode *N);
int Max(int a, int b);
AVLNode *NewNode(int key);
AVLNode *RightRotate(AVLNode *y);
AVLNode *LeftRotate(AVLNode *x);
int GetBalance(AVLNode *N);
AVLNode *AVL_Insert(AVLNode *node, int key);
AVLNode *MinValueNode(AVLNode *node);
AVLNode *AVL_Delete(AVLNode *root, int key);
void AVL_InOrder(AVLNode *root);

#endif
