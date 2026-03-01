#include <stdlib.h>
#include <math.h>
#include "include/sort/radix_sort.h"

int GetMax(int *a, int n) {
    int max = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

void CountSort(int *a, int n, int exp) {
    int *output = (int *)malloc(n * sizeof(int));
    int count[10] = {0};
    for (int i = 0; i < n; i++) {
        count[(a[i] / exp) % 10]++;
    }
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        output[count[(a[i] / exp) % 10] - 1] = a[i];
        count[(a[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) {
        a[i] = output[i];
    }
    free(output);
}

void RadixSort(int *a, int n) {
    int max = GetMax(a, n);
    for (int exp = 1; max / exp > 0; exp *= 10) {
        CountSort(a, n, exp);
    }
}
