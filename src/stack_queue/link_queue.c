#include <stdio.h>
#include <stdlib.h>
#include "include/stack_queue/link_queue.h"

void InitLinkQueue(LinkQueue *Q) {
    Q->front = Q->rear = (QNode *)malloc(sizeof(QNode));
    Q->front->next = NULL;
}

int LinkQueueEmpty(LinkQueue Q) {
    return Q.front == Q.rear;
}

void LinkEnQueue(LinkQueue *Q, int x) {
    QNode *p = (QNode *)malloc(sizeof(QNode));
    p->data = x;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
}

int LinkDeQueue(LinkQueue *Q, int *x) {
    if (Q->front == Q->rear) {
        return 0;
    }
    QNode *p = Q->front->next;
    *x = p->data;
    Q->front->next = p->next;
    if (Q->rear == p) {
        Q->rear = Q->front;
    }
    free(p);
    return 1;
}

int LinkGetHead(LinkQueue Q, int *x) {
    if (Q.front == Q.rear) {
        return 0;
    }
    *x = Q.front->next->data;
    return 1;
}
