#include <stdio.h>
#include <string.h>
#include "include/sort/insert_sort.h"
#include "include/sort/bubble_sort.h"
#include "include/sort/selection_sort.h"
#include "include/sort/shell_sort.h"
#include "include/sort/quick_sort.h"
#include "include/sort/heap_sort.h"
#include "include/sort/merge_sort.h"
#include "include/sort/radix_sort.h"

void PrintArray(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void CopyArray(int *src, int *dest, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int main() {
    int arr[] = {49, 38, 65, 97, 76, 13, 27, 49, 55, 4};
    int n = 10;
    int temp[20];

    printf("=== Sorting Algorithms Test ===\n");
    printf("Original array: ");
    PrintArray(arr, n);

    printf("\n--- Bubble Sort ---\n");
    CopyArray(arr, temp, n);
    BubbleSort(temp, n);
    printf("After sort: ");
    PrintArray(temp, n);

    printf("\n--- Selection Sort ---\n");
    CopyArray(arr, temp, n);
    SelectionSort(temp, n);
    printf("After sort: ");
    PrintArray(temp, n);

    printf("\n--- Insert Sort ---\n");
    CopyArray(arr, temp, n);
    InsertSort(temp, n);
    printf("After sort: ");
    PrintArray(temp, n);

    printf("\n--- Binary Insert Sort ---\n");
    CopyArray(arr, temp, n);
    BinaryInsertSort(temp, n);
    printf("After sort: ");
    PrintArray(temp, n);

    printf("\n--- Shell Sort ---\n");
    CopyArray(arr, temp, n);
    ShellSort(temp, n);
    printf("After sort: ");
    PrintArray(temp, n);

    printf("\n--- Quick Sort ---\n");
    CopyArray(arr, temp, n);
    QuickSort(temp, 0, n - 1);
    printf("After sort: ");
    PrintArray(temp, n);

    printf("\n--- Heap Sort ---\n");
    CopyArray(arr, temp, n);
    HeapSort(temp, n);
    printf("After sort: ");
    PrintArray(temp, n);

    printf("\n--- Merge Sort ---\n");
    CopyArray(arr, temp, n);
    MergeSort(temp, 0, n - 1);
    printf("After sort: ");
    PrintArray(temp, n);

    printf("\n--- Radix Sort ---\n");
    CopyArray(arr, temp, n);
    RadixSort(temp, n);
    printf("After sort: ");
    PrintArray(temp, n);

    return 0;
}
