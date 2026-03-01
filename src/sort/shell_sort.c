#include "include/sort/shell_sort.h"

void ShellSort(int *a, int n) {
    for (int dk = n / 2; dk >= 1; dk = dk / 2) {
        for (int i = dk; i < n; i++) {
            if (a[i] < a[i - dk]) {
                int temp = a[i];
                int j;
                for (j = i - dk; j >= 0 && temp < a[j]; j -= dk) {
                    a[j + dk] = a[j];
                }
                a[j + dk] = temp;
            }
        }
    }
}
