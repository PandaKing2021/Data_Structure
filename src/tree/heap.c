#include <stdio.h>
#include <stdlib.h>
#include "include/tree/heap.h"

void InitMaxHeap(MaxHeap *H) {
    H->length = 0;
}

void InitMinHeap(MinHeap *H) {
    H->length = 0;
}

void HeapAdjust(int *a, int k, int len) {
    a[0] = a[k];
    for (int i = 2 * k; i <= len; i *= 2) {
        if (i < len && a[i] < a[i + 1]) i++;
        if (a[0] >= a[i]) break;
        a[k] = a[i];
        k = i;
    }
    a[k] = a[0];
}

void BuildMaxHeap(MaxHeap *H) {
    for (int i = H->length / 2; i > 0; i--) {
        HeapAdjust(H->data, i, H->length);
    }
}

void BuildMinHeap(MinHeap *H) {
    for (int i = H->length / 2; i > 0; i--) {
        H->data[0] = H->data[i];
        for (int j = 2 * i; j <= H->length; j *= 2) {
            if (j < H->length && H->data[j] > H->data[j + 1]) j++;
            if (H->data[0] <= H->data[j]) break;
            H->data[i] = H->data[j];
            i = j;
        }
        H->data[i] = H->data[0];
    }
}

int HeapInsertMax(MaxHeap *H, int x) {
    if (H->length >= MAX_SIZE - 1) return 0;
    H->data[++H->length] = x;
    int i = H->length;
    while (i > 1 && H->data[i] > H->data[i / 2]) {
        int temp = H->data[i];
        H->data[i] = H->data[i / 2];
        H->data[i / 2] = temp;
        i = i / 2;
    }
    return 1;
}

int HeapInsertMin(MinHeap *H, int x) {
    if (H->length >= MAX_SIZE - 1) return 0;
    H->data[++H->length] = x;
    int i = H->length;
    while (i > 1 && H->data[i] < H->data[i / 2]) {
        int temp = H->data[i];
        H->data[i] = H->data[i / 2];
        H->data[i / 2] = temp;
        i = i / 2;
    }
    return 1;
}

int HeapDeleteMax(MaxHeap *H, int *x) {
    if (H->length == 0) return 0;
    *x = H->data[1];
    H->data[1] = H->data[H->length--];
    HeapAdjust(H->data, 1, H->length);
    return 1;
}

int HeapDeleteMin(MinHeap *H, int *x) {
    if (H->length == 0) return 0;
    *x = H->data[1];
    H->data[1] = H->data[H->length--];
    for (int i = 1; 2 * i <= H->length; ) {
        int j = 2 * i;
        if (j < H->length && H->data[j] > H->data[j + 1]) j++;
        if (H->data[i] <= H->data[j]) break;
        int temp = H->data[i];
        H->data[i] = H->data[j];
        H->data[j] = temp;
        i = j;
    }
    return 1;
}

void HeapSort(int *a, int n) {
    for (int i = n / 2; i > 0; i--) {
        a[0] = a[i];
        for (int j = 2 * i; j <= n; j *= 2) {
            if (j < n && a[j] < a[j + 1]) j++;
            if (a[0] >= a[j]) break;
            a[i] = a[j];
            i = j;
        }
        a[i] = a[0];
    }
    for (int i = n; i > 1; i--) {
        int temp = a[1];
        a[1] = a[i];
        a[i] = temp;
        a[0] = a[1];
        int k = 1;
        for (int j = 2 * k; j <= i - 1; j *= 2) {
            if (j < i - 1 && a[j] < a[j + 1]) j++;
            if (a[0] >= a[j]) break;
            a[k] = a[j];
            k = j;
        }
        a[k] = a[0];
    }
}
