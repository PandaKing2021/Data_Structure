#include <stdio.h>
#include <stdlib.h>
#include "include/stack_queue/seq_queue.h"

void InitQueue(SeqQueue *Q) {
    Q->front = Q->rear = 0;
}

int QueueEmpty(SeqQueue Q) {
    return Q.front == Q.rear;
}

int QueueFull(SeqQueue Q) {
    return (Q.rear + 1) % MAX_SIZE == Q.front;
}

int EnQueue(SeqQueue *Q, int x) {
    if ((Q->rear + 1) % MAX_SIZE == Q->front) {
        return 0;
    }
    Q->data[Q->rear] = x;
    Q->rear = (Q->rear + 1) % MAX_SIZE;
    return 1;
}

int DeQueue(SeqQueue *Q, int *x) {
    if (Q->front == Q->rear) {
        return 0;
    }
    *x = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAX_SIZE;
    return 1;
}

int GetHead(SeqQueue Q, int *x) {
    if (Q.front == Q.rear) {
        return 0;
    }
    *x = Q.data[Q.front];
    return 1;
}
