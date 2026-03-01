#ifndef LINK_STACK_H
#define LINK_STACK_H

typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode, *LinkStack;

void InitLinkStack(LinkStack *S);
int LinkStackEmpty(LinkStack S);
int LinkPush(LinkStack *S, int x);
int LinkPop(LinkStack *S, int *x);
int LinkGetTop(LinkStack S, int *x);

#endif
