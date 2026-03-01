#ifndef SEQ_STACK_H
#define SEQ_STACK_H

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int top;
} SeqStack;

void InitStack(SeqStack *S);
int StackEmpty(SeqStack S);
int StackFull(SeqStack S);
int Push(SeqStack *S, int x);
int Pop(SeqStack *S, int *x);
int GetTop(SeqStack S, int *x);

#endif
