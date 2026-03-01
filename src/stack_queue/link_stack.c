#include <stdio.h>
#include <stdlib.h>
#include "include/stack_queue/link_stack.h"

void InitLinkStack(LinkStack *S) {
    *S = NULL;
}

int LinkStackEmpty(LinkStack S) {
    return S == NULL;
}

int LinkPush(LinkStack *S, int x) {
    StackNode *p = (StackNode *)malloc(sizeof(StackNode));
    if (!p) return 0;
    p->data = x;
    p->next = *S;
    *S = p;
    return 1;
}

int LinkPop(LinkStack *S, int *x) {
    if (*S == NULL) {
        return 0;
    }
    StackNode *p = *S;
    *x = p->data;
    *S = p->next;
    free(p);
    return 1;
}

int LinkGetTop(LinkStack S, int *x) {
    if (S == NULL) {
        return 0;
    }
    *x = S->data;
    return 1;
}
