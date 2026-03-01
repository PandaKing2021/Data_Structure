#ifndef HEAP_H
#define HEAP_H

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int length;
} MaxHeap;

typedef struct {
    int data[MAX_SIZE];
    int length;
} MinHeap;

void InitMaxHeap(MaxHeap *H);
void InitMinHeap(MinHeap *H);
void HeapAdjust(int *a, int k, int len);
void BuildMaxHeap(MaxHeap *H);
void BuildMinHeap(MinHeap *H);
int HeapInsertMax(MaxHeap *H, int x);
int HeapInsertMin(MinHeap *H, int x);
int HeapDeleteMax(MaxHeap *H, int *x);
int HeapDeleteMin(MinHeap *H, int *x);
void HeapSort(int *a, int n);

#endif
