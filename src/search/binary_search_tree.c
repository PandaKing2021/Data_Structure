#include <stdio.h>
#include <stdlib.h>
#include "include/search/binary_search_tree.h"

BSTNode *BST_Insert(BSTNode *T, int key) {
    if (T == NULL) {
        T = (BSTNode *)malloc(sizeof(BSTNode));
        T->key = key;
        T->lchild = T->rchild = NULL;
    } else if (key < T->key) {
        T->lchild = BST_Insert(T->lchild, key);
    } else if (key > T->key) {
        T->rchild = BST_Insert(T->rchild, key);
    }
    return T;
}

BSTNode *BST_Search(BSTNode *T, int key) {
    if (T == NULL || T->key == key) {
        return T;
    } else if (key < T->key) {
        return BST_Search(T->lchild, key);
    } else {
        return BST_Search(T->rchild, key);
    }
}

BSTNode *BST_Delete(BSTNode *T, int key) {
    if (T == NULL) return NULL;
    if (key < T->key) {
        T->lchild = BST_Delete(T->lchild, key);
    } else if (key > T->key) {
        T->rchild = BST_Delete(T->rchild, key);
    } else {
        if (T->lchild == NULL) {
            BSTNode *temp = T->rchild;
            free(T);
            return temp;
        } else if (T->rchild == NULL) {
            BSTNode *temp = T->lchild;
            free(T);
            return temp;
        }
        BSTNode *temp = T->rchild;
        while (temp->lchild != NULL) {
            temp = temp->lchild;
        }
        T->key = temp->key;
        T->rchild = BST_Delete(T->rchild, temp->key);
    }
    return T;
}

void BST_InOrder(BSTNode *T) {
    if (T) {
        BST_InOrder(T->lchild);
        printf("%d ", T->key);
        BST_InOrder(T->rchild);
    }
}
