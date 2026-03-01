#include "../../include/linear_list/multi_array.h"
#include <stdio.h>

int main() {
    printf("=== Multi-dimensional Array Storage Tests ===\n\n");

    int rows = 3, cols = 4;

    printf("2D Array (3x4) Row-Major Index:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("a[%d][%d] -> index %d\n", i, j, RowMajorIndex(rows, cols, i, j));
        }
    }

    printf("\n2D Array (3x4) Column-Major Index:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("a[%d][%d] -> index %d\n", i, j, ColMajorIndex(rows, cols, i, j));
        }
    }

    int d1 = 2, d2 = 3, d3 = 4;
    printf("\n3D Array (2x3x4) Row-Major Index:\n");
    for (int i = 0; i < d1; i++) {
        for (int j = 0; j < d2; j++) {
            for (int k = 0; k < d3; k++) {
                printf("a[%d][%d][%d] -> index %d\n", i, j, k, RowMajorIndex3D(d1, d2, d3, i, j, k));
            }
        }
    }

    printf("\n3D Array (2x3x4) Column-Major Index:\n");
    for (int i = 0; i < d1; i++) {
        for (int j = 0; j < d2; j++) {
            for (int k = 0; k < d3; k++) {
                printf("a[%d][%d][%d] -> index %d\n", i, j, k, ColMajorIndex3D(d1, d2, d3, i, j, k));
            }
        }
    }

    int dims[] = {2, 3, 4};
    int indices[] = {1, 2, 1};
    printf("\nGeneral 3D Array [2][3][4] Row-Major Index for indices [1][2][1]: %d\n",
           GeneralRowMajorIndex(dims, 3, indices));
    printf("General 3D Array [2][3][4] Column-Major Index for indices [1][2][1]: %d\n",
           GeneralColMajorIndex(dims, 3, indices));

    printf("\n=== All Tests Passed ===\n");
    return 0;
}
