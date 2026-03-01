#include <stdio.h>
#include <stdlib.h>
#include "include/linear_list/double_link_list.h"

void InitList(DLinkList *L) {
    *L = (DNode *)malloc(sizeof(DNode));
    (*L)->prior = NULL;
    (*L)->next = NULL;
}

int ListEmpty(DLinkList L) {
    return L->next == NULL;
}

int ListLength(DLinkList L) {
    int len = 0;
    DNode *p = L->next;
    while (p) {
        len++;
        p = p->next;
    }
    return len;
}

int GetElem(DLinkList L, int i, int *e) {
    int j = 0;
    DNode *p = L->next;
    while (p && j < i - 1) {
        p = p->next;
        j++;
    }
    if (!p || j > i - 1) {
        return 0;
    }
    *e = p->data;
    return 1;
}

DNode *LocateElem(DLinkList L, int e) {
    DNode *p = L->next;
    while (p && p->data != e) {
        p = p->next;
    }
    return p;
}

int ListInsert(DLinkList *L, int i, int e) {
    int j = 0;
    DNode *p = *L;
    while (p && j < i - 1) {
        p = p->next;
        j++;
    }
    if (!p || j > i - 1) {
        return 0;
    }
    DNode *s = (DNode *)malloc(sizeof(DNode));
    s->data = e;
    s->next = p->next;
    s->prior = p;
    if (p->next) {
        p->next->prior = s;
    }
    p->next = s;
    return 1;
}

int ListDelete(DLinkList *L, int i, int *e) {
    int j = 0;
    DNode *p = *L;
    while (p->next && j < i - 1) {
        p = p->next;
        j++;
    }
    if (!(p->next) || j > i - 1) {
        return 0;
    }
    DNode *q = p->next;
    *e = q->data;
    p->next = q->next;
    if (q->next) {
        q->next->prior = p;
    }
    free(q);
    return 1;
}

void PrintList(DLinkList L) {
    printf("List: ");
    DNode *p = L->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
