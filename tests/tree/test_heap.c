#include <stdio.h>
#include "include/tree/heap.h"

int main() {
    printf("=== Max Heap Test ===\n");
    MaxHeap H;
    InitMaxHeap(&H);

    printf("Insert: 50, 30, 70, 20, 40, 60, 80\n");
    HeapInsertMax(&H, 50);
    HeapInsertMax(&H, 30);
    HeapInsertMax(&H, 70);
    HeapInsertMax(&H, 20);
    HeapInsertMax(&H, 40);
    HeapInsertMax(&H, 60);
    HeapInsertMax(&H, 80);

    printf("Heap elements: ");
    for (int i = 1; i <= H.length; i++) {
        printf("%d ", H.data[i]);
    }
    printf("\n");

    int x;
    HeapDeleteMax(&H, &x);
    printf("Deleted max: %d\n", x);
    printf("Heap after deletion: ");
    for (int i = 1; i <= H.length; i++) {
        printf("%d ", H.data[i]);
    }
    printf("\n");

    printf("\n=== Min Heap Test ===\n");
    MinHeap MH;
    InitMinHeap(&MH);

    printf("Insert: 50, 30, 70, 20, 40, 60, 80\n");
    HeapInsertMin(&MH, 50);
    HeapInsertMin(&MH, 30);
    HeapInsertMin(&MH, 70);
    HeapInsertMin(&MH, 20);
    HeapInsertMin(&MH, 40);
    HeapInsertMin(&MH, 60);
    HeapInsertMin(&MH, 80);

    printf("Heap elements: ");
    for (int i = 1; i <= MH.length; i++) {
        printf("%d ", MH.data[i]);
    }
    printf("\n");

    HeapDeleteMin(&MH, &x);
    printf("Deleted min: %d\n", x);
    printf("Heap after deletion: ");
    for (int i = 1; i <= MH.length; i++) {
        printf("%d ", MH.data[i]);
    }
    printf("\n");

    return 0;
}
