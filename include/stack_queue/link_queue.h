#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H

typedef struct QNode {
    int data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
} LinkQueue;

void InitLinkQueue(LinkQueue *Q);
int LinkQueueEmpty(LinkQueue Q);
void LinkEnQueue(LinkQueue *Q, int x);
int LinkDeQueue(LinkQueue *Q, int *x);
int LinkGetHead(LinkQueue Q, int *x);

#endif
