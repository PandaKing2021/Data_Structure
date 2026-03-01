#include "include/sort/heap_sort.h"

void HeapAdjust(int *a, int k, int len) {
    int temp = a[k];
    for (int i = 2 * k + 1; i < len; i = 2 * i + 1) {
        if (i + 1 < len && a[i] < a[i + 1]) i++;
        if (temp >= a[i]) break;
        a[k] = a[i];
        k = i;
    }
    a[k] = temp;
}

void HeapSort(int *a, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        HeapAdjust(a, i, n);
    }
    for (int i = n - 1; i > 0; i--) {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        HeapAdjust(a, 0, i);
    }
}
