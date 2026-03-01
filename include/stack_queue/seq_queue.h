#ifndef SEQ_QUEUE_H
#define SEQ_QUEUE_H

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
} SeqQueue;

void InitQueue(SeqQueue *Q);
int QueueEmpty(SeqQueue Q);
int QueueFull(SeqQueue Q);
int EnQueue(SeqQueue *Q, int x);
int DeQueue(SeqQueue *Q, int *x);
int GetHead(SeqQueue Q, int *x);

#endif
