#include <stdio.h>
#include <stdlib.h>
#include "include/search/avl_tree.h"

int Height(AVLNode *N) {
    if (N == NULL) return 0;
    return N->height;
}

int Max(int a, int b) {
    return (a > b) ? a : b;
}

AVLNode *NewNode(int key) {
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    node->key = key;
    node->lchild = node->rchild = NULL;
    node->height = 1;
    return node;
}

AVLNode *RightRotate(AVLNode *y) {
    AVLNode *x = y->lchild;
    AVLNode *T2 = x->rchild;
    x->rchild = y;
    y->lchild = T2;
    y->height = Max(Height(y->lchild), Height(y->rchild)) + 1;
    x->height = Max(Height(x->lchild), Height(x->rchild)) + 1;
    return x;
}

AVLNode *LeftRotate(AVLNode *x) {
    AVLNode *y = x->rchild;
    AVLNode *T2 = y->lchild;
    y->lchild = x;
    x->rchild = T2;
    x->height = Max(Height(x->lchild), Height(x->rchild)) + 1;
    y->height = Max(Height(y->lchild), Height(y->rchild)) + 1;
    return y;
}

int GetBalance(AVLNode *N) {
    if (N == NULL) return 0;
    return Height(N->lchild) - Height(N->rchild);
}

AVLNode *AVL_Insert(AVLNode *node, int key) {
    if (node == NULL) return NewNode(key);
    if (key < node->key) {
        node->lchild = AVL_Insert(node->lchild, key);
    } else if (key > node->key) {
        node->rchild = AVL_Insert(node->rchild, key);
    } else {
        return node;
    }
    node->height = 1 + Max(Height(node->lchild), Height(node->rchild));
    int balance = GetBalance(node);
    if (balance > 1 && key < node->lchild->key) {
        return RightRotate(node);
    }
    if (balance < -1 && key > node->rchild->key) {
        return LeftRotate(node);
    }
    if (balance > 1 && key > node->lchild->key) {
        node->lchild = LeftRotate(node->lchild);
        return RightRotate(node);
    }
    if (balance < -1 && key < node->rchild->key) {
        node->rchild = RightRotate(node->rchild);
        return LeftRotate(node);
    }
    return node;
}

AVLNode *MinValueNode(AVLNode *node) {
    AVLNode *current = node;
    while (current->lchild != NULL) {
        current = current->lchild;
    }
    return current;
}

AVLNode *AVL_Delete(AVLNode *root, int key) {
    if (root == NULL) return root;
    if (key < root->key) {
        root->lchild = AVL_Delete(root->lchild, key);
    } else if (key > root->key) {
        root->rchild = AVL_Delete(root->rchild, key);
    } else {
        if ((root->lchild == NULL) || (root->rchild == NULL)) {
            AVLNode *temp = root->lchild ? root->lchild : root->rchild;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            AVLNode *temp = MinValueNode(root->rchild);
            root->key = temp->key;
            root->rchild = AVL_Delete(root->rchild, temp->key);
        }
    }
    if (root == NULL) return root;
    root->height = 1 + Max(Height(root->lchild), Height(root->rchild));
    int balance = GetBalance(root);
    if (balance > 1 && GetBalance(root->lchild) >= 0) {
        return RightRotate(root);
    }
    if (balance > 1 && GetBalance(root->lchild) < 0) {
        root->lchild = LeftRotate(root->lchild);
        return RightRotate(root);
    }
    if (balance < -1 && GetBalance(root->rchild) <= 0) {
        return LeftRotate(root);
    }
    if (balance < -1 && GetBalance(root->rchild) > 0) {
        root->rchild = RightRotate(root->rchild);
        return LeftRotate(root);
    }
    return root;
}

void AVL_InOrder(AVLNode *root) {
    if (root != NULL) {
        AVL_InOrder(root->lchild);
        printf("%d ", root->key);
        AVL_InOrder(root->rchild);
    }
}
