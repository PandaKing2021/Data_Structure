#include <stdio.h>
#include <stdlib.h>
#include "../../include/stack_queue/seq_stack.h"

void InitStack(SeqStack *S) {
    S->top = -1;
}

int StackEmpty(SeqStack S) {
    return S.top == -1;
}

int StackFull(SeqStack S) {
    return S.top == MAX_SIZE - 1;
}

int Push(SeqStack *S, int x) {
    if (S->top == MAX_SIZE - 1) {
        return 0;
    }
    S->data[++S->top] = x;
    return 1;
}

int Pop(SeqStack *S, int *x) {
    if (S->top == -1) {
        return 0;
    }
    *x = S->data[S->top--];
    return 1;
}

int GetTop(SeqStack S, int *x) {
    if (S.top == -1) {
        return 0;
    }
    *x = S.data[S.top];
    return 1;
}
