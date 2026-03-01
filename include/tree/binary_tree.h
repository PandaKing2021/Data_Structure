#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef struct BTNode {
    int data;
    struct BTNode *lchild;
    struct BTNode *rchild;
} BTNode;

void CreateBTree(BTNode **T);
void PreOrder(BTNode *T);
void InOrder(BTNode *T);
void PostOrder(BTNode *T);
void LevelOrder(BTNode *T);
int TreeDepth(BTNode *T);
int NodeCount(BTNode *T);
int LeafCount(BTNode *T);

typedef struct ThreadNode {
    int data;
    struct ThreadNode *lchild, *rchild;
    int ltag, rtag;
} ThreadNode;

void CreateThreadTree(ThreadNode **T);
void InThread(ThreadNode *p, ThreadNode **pre);
void CreateInThread(ThreadNode *T);
ThreadNode *FirstNode(ThreadNode *p);
ThreadNode *NextNode(ThreadNode *p);
void InOrderThread(ThreadNode *T);

#endif
