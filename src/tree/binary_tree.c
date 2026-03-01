#include <stdio.h>
#include <stdlib.h>
#include "include/tree/binary_tree.h"

void CreateBTree(BTNode **T) {
    int ch;
    scanf("%d", &ch);
    if (ch == -1) {
        *T = NULL;
    } else {
        *T = (BTNode *)malloc(sizeof(BTNode));
        (*T)->data = ch;
        CreateBTree(&(*T)->lchild);
        CreateBTree(&(*T)->rchild);
    }
}

void PreOrder(BTNode *T) {
    if (T) {
        printf("%d ", T->data);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void InOrder(BTNode *T) {
    if (T) {
        InOrder(T->lchild);
        printf("%d ", T->data);
        InOrder(T->rchild);
    }
}

void PostOrder(BTNode *T) {
    if (T) {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        printf("%d ", T->data);
    }
}

void LevelOrder(BTNode *T) {
    BTNode *queue[100];
    int front = 0, rear = 0;
    if (T) {
        queue[rear++] = T;
    }
    while (front < rear) {
        BTNode *p = queue[front++];
        printf("%d ", p->data);
        if (p->lchild) queue[rear++] = p->lchild;
        if (p->rchild) queue[rear++] = p->rchild;
    }
}

int TreeDepth(BTNode *T) {
    if (!T) return 0;
    int left = TreeDepth(T->lchild);
    int right = TreeDepth(T->rchild);
    return (left > right ? left : right) + 1;
}

int NodeCount(BTNode *T) {
    if (!T) return 0;
    return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
}

int LeafCount(BTNode *T) {
    if (!T) return 0;
    if (!T->lchild && !T->rchild) return 1;
    return LeafCount(T->lchild) + LeafCount(T->rchild);
}

void CreateThreadTree(ThreadNode **T) {
    int ch;
    scanf("%d", &ch);
    if (ch == -1) {
        *T = NULL;
    } else {
        *T = (ThreadNode *)malloc(sizeof(ThreadNode));
        (*T)->data = ch;
        (*T)->ltag = (*T)->rtag = 0;
        CreateThreadTree(&(*T)->lchild);
        CreateThreadTree(&(*T)->rchild);
    }
}

void InThread(ThreadNode *p, ThreadNode **pre) {
    if (p) {
        InThread(p->lchild, pre);
        if (!p->lchild) {
            p->lchild = *pre;
            p->ltag = 1;
        }
        if (*pre && !(*pre)->rchild) {
            (*pre)->rchild = p;
            (*pre)->rtag = 1;
        }
        *pre = p;
        InThread(p->rchild, pre);
    }
}

void CreateInThread(ThreadNode *T) {
    ThreadNode *pre = NULL;
    if (T) {
        InThread(T, &pre);
        pre->rtag = 1;
        pre->rchild = NULL;
    }
}

ThreadNode *FirstNode(ThreadNode *p) {
    while (p->ltag == 0) {
        p = p->lchild;
    }
    return p;
}

ThreadNode *NextNode(ThreadNode *p) {
    if (p->rtag == 0) {
        return FirstNode(p->rchild);
    }
    return p->rchild;
}

void InOrderThread(ThreadNode *T) {
    for (ThreadNode *p = FirstNode(T); p; p = NextNode(p)) {
        printf("%d ", p->data);
    }
}
