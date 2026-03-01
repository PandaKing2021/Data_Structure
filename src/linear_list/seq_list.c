#include <stdio.h>
#include <stdlib.h>
#include "include/linear_list/seq_list.h"

void InitList(SeqList *L) {
    L->length = 0;
}

int ListEmpty(SeqList L) {
    return L.length == 0;
}

int ListLength(SeqList L) {
    return L.length;
}

int GetElem(SeqList L, int i, int *e) {
    if (i < 1 || i > L.length) {
        return 0;
    }
    *e = L.data[i - 1];
    return 1;
}

int LocateElem(SeqList L, int e) {
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] == e) {
            return i + 1;
        }
    }
    return 0;
}

int ListInsert(SeqList *L, int i, int e) {
    if (i < 1 || i > L->length + 1 || L->length >= MAX_SIZE) {
        return 0;
    }
    for (int j = L->length; j >= i; j--) {
        L->data[j] = L->data[j - 1];
    }
    L->data[i - 1] = e;
    L->length++;
    return 1;
}

int ListDelete(SeqList *L, int i, int *e) {
    if (i < 1 || i > L->length) {
        return 0;
    }
    *e = L->data[i - 1];
    for (int j = i; j < L->length; j++) {
        L->data[j - 1] = L->data[j];
    }
    L->length--;
    return 1;
}

void PrintList(SeqList L) {
    printf("List: ");
    for (int i = 0; i < L.length; i++) {
        printf("%d ", L.data[i]);
    }
    printf("\n");
}
