#include "include/sort/insert_sort.h"

void InsertSort(int *a, int n) {
    for (int i = 1; i < n; i++) {
        if (a[i] < a[i - 1]) {
            int temp = a[i];
            int j;
            for (j = i - 1; j >= 0 && temp < a[j]; j--) {
                a[j + 1] = a[j];
            }
            a[j + 1] = temp;
        }
    }
}

void BinaryInsertSort(int *a, int n) {
    for (int i = 1; i < n; i++) {
        int temp = a[i];
        int low = 0, high = i - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (temp < a[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        for (int j = i - 1; j >= high + 1; j--) {
            a[j + 1] = a[j];
        }
        a[high + 1] = temp;
    }
}
