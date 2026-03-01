#ifndef DOUBLE_LINK_LIST_H
#define DOUBLE_LINK_LIST_H

typedef struct DNode {
    int data;
    struct DNode *prior;
    struct DNode *next;
} DNode, *DLinkList;

void InitList(DLinkList *L);
int ListEmpty(DLinkList L);
int ListLength(DLinkList L);
int GetElem(DLinkList L, int i, int *e);
DNode *LocateElem(DLinkList L, int e);
int ListInsert(DLinkList *L, int i, int e);
int ListDelete(DLinkList *L, int i, int *e);
void PrintList(DLinkList L);

#endif
