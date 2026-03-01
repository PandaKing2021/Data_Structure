#include <stdio.h>
#include <stdlib.h>
#include "include/linear_list/link_list.h"

void InitList(LinkList *L) {
    *L = (LNode *)malloc(sizeof(LNode));
    (*L)->next = NULL;
}

int ListEmpty(LinkList L) {
    return L->next == NULL;
}

int ListLength(LinkList L) {
    int len = 0;
    LNode *p = L->next;
    while (p) {
        len++;
        p = p->next;
    }
    return len;
}

int GetElem(LinkList L, int i, int *e) {
    int j = 0;
    LNode *p = L->next;
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

LNode *LocateElem(LinkList L, int e) {
    LNode *p = L->next;
    while (p && p->data != e) {
        p = p->next;
    }
    return p;
}

int ListInsert(LinkList *L, int i, int e) {
    int j = 0;
    LNode *p = *L;
    while (p && j < i - 1) {
        p = p->next;
        j++;
    }
    if (!p || j > i - 1) {
        return 0;
    }
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return 1;
}

int ListDelete(LinkList *L, int i, int *e) {
    int j = 0;
    LNode *p = *L;
    while (p->next && j < i - 1) {
        p = p->next;
        j++;
    }
    if (!(p->next) || j > i - 1) {
        return 0;
    }
    LNode *q = p->next;
    *e = q->data;
    p->next = q->next;
    free(q);
    return 1;
}

void PrintList(LinkList L) {
    printf("List: ");
    LNode *p = L->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
