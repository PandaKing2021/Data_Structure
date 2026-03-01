#ifndef LINK_LIST_H
#define LINK_LIST_H

typedef struct LNode {
    int data;
    struct LNode *next;
} LNode, *LinkList;

void InitList(LinkList *L);
int ListEmpty(LinkList L);
int ListLength(LinkList L);
int GetElem(LinkList L, int i, int *e);
LNode *LocateElem(LinkList L, int e);
int ListInsert(LinkList *L, int i, int e);
int ListDelete(LinkList *L, int i, int *e);
void PrintList(LinkList L);

#endif
