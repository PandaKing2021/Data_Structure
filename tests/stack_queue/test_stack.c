#include <stdio.h>
#include "include/stack_queue/seq_stack.h"
#include "include/stack_queue/link_stack.h"

int main() {
    printf("=== Sequential Stack Test ===\n");
    SeqStack S;
    InitStack(&S);

    printf("Push 10, 20, 30, 40, 50\n");
    Push(&S, 10);
    Push(&S, 20);
    Push(&S, 30);
    Push(&S, 40);
    Push(&S, 50);

    int x;
    GetTop(S, &x);
    printf("Top element: %d\n", x);
    printf("Empty: %d\n", StackEmpty(S));

    printf("Pop elements:\n");
    while (!StackEmpty(S)) {
        Pop(&S, &x);
        printf("%d ", x);
    }
    printf("\n");

    printf("\n=== Linked Stack Test ===\n");
    LinkStack LS;
    InitLinkStack(&LS);

    printf("Push 100, 200, 300\n");
    LinkPush(&LS, 100);
    LinkPush(&LS, 200);
    LinkPush(&LS, 300);

    LinkGetTop(LS, &x);
    printf("Top element: %d\n", x);

    printf("Pop elements:\n");
    while (!LinkStackEmpty(LS)) {
        LinkPop(&LS, &x);
        printf("%d ", x);
    }
    printf("\n");

    return 0;
}
