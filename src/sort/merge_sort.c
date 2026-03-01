#include <stdlib.h>
#include <string.h>
#include "include/sort/merge_sort.h"

void Merge(int *a, int low, int mid, int high) {
    int *b = (int *)malloc((high - low + 1) * sizeof(int));
    int i = low, j = mid + 1, k = 0;
    while (i <= mid && j <= high) {
        if (a[i] <= a[j]) {
            b[k++] = a[i++];
        } else {
            b[k++] = a[j++];
        }
    }
    while (i <= mid) {
        b[k++] = a[i++];
    }
    while (j <= high) {
        b[k++] = a[j++];
    }
    for (int p = 0, q = low; p < k; p++, q++) {
        a[q] = b[p];
    }
    free(b);
}

void MergeSort(int *a, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        MergeSort(a, low, mid);
        MergeSort(a, mid + 1, high);
        Merge(a, low, mid, high);
    }
}
