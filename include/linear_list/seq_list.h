#ifndef SEQ_LIST_H
#define SEQ_LIST_H

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int length;
} SeqList;

void InitList(SeqList *L);
int ListEmpty(SeqList L);
int ListLength(SeqList L);
int GetElem(SeqList L, int i, int *e);
int LocateElem(SeqList L, int e);
int ListInsert(SeqList *L, int i, int e);
int ListDelete(SeqList *L, int i, int *e);
void PrintList(SeqList L);

#endif
