#include <stdio.h>
#include "include/stack_queue/seq_queue.h"
#include "include/stack_queue/link_queue.h"

int main() {
    printf("=== Sequential Queue Test ===\n");
    SeqQueue Q;
    InitQueue(&Q);

    printf("Enqueue 10, 20, 30, 40, 50\n");
    EnQueue(&Q, 10);
    EnQueue(&Q, 20);
    EnQueue(&Q, 30);
    EnQueue(&Q, 40);
    EnQueue(&Q, 50);

    int x;
    GetHead(Q, &x);
    printf("Front element: %d\n", x);
    printf("Empty: %d\n", QueueEmpty(Q));

    printf("Dequeue elements:\n");
    while (!QueueEmpty(Q)) {
        DeQueue(&Q, &x);
        printf("%d ", x);
    }
    printf("\n");

    printf("\n=== Linked Queue Test ===\n");
    LinkQueue LQ;
    InitLinkQueue(&LQ);

    printf("Enqueue 100, 200, 300\n");
    LinkEnQueue(&LQ, 100);
    LinkEnQueue(&LQ, 200);
    LinkEnQueue(&LQ, 300);

    LinkGetHead(LQ, &x);
    printf("Front element: %d\n", x);

    printf("Dequeue elements:\n");
    while (!LinkQueueEmpty(LQ)) {
        LinkDeQueue(&LQ, &x);
        printf("%d ", x);
    }
    printf("\n");

    return 0;
}
