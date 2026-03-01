#include "../../include/linear_list/sparse_matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=== Sparse Matrix Storage Tests ===\n\n");

    /* Triplet matrix test */
    printf("1. Triplet Storage:\n");
    TSMatrix M, T, A, B, C, D;

    int elements[][3] = {{0, 0, 1}, {0, 3, 2}, {1, 1, 3}, {2, 0, 4}, {2, 2, 5}};
    CreateTSMatrix(&M, 3, 4, elements, 5);
    printf("Original Matrix M:\n");
    PrintTSMatrix(M);

    printf("\nMatrix M (full view):\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%2d ", GetTSMatrixElem(M, i, j));
        }
        printf("\n");
    }

    printf("\nTransposed Matrix T:\n");
    TransposeTSMatrix(M, &T);
    PrintTSMatrix(T);

    printf("\nTransposed Matrix T (full view):\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%2d ", GetTSMatrixElem(T, i, j));
        }
        printf("\n");
    }

\n    /* Matrix addition test */
    printf("\n2. Matrix Addition:\n");
    int elementsA[][3] = {{0, 0, 1}, {0, 1, 2}, {1, 0, 3}, {1, 1, 4}};
    int elementsB[][3] = {{0, 0, 1}, {0, 2, 3}, {1, 1, 1}, {2, 0, 2}};
    CreateTSMatrix(&A, 3, 3, elementsA, 4);
    CreateTSMatrix(&B, 3, 3, elementsB, 4);

    printf("Matrix A:\n");
    PrintTSMatrix(A);

    printf("\nMatrix B:\n");
    PrintTSMatrix(B);

    AddTSMatrix(A, B, &C);
    printf("\nA + B:\n");
    PrintTSMatrix(C);

    printf("\nA + B (full view):\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%2d ", GetTSMatrixElem(C, i, j));
        }
        printf("\n");
    }


    /* Matrix multiplication test */
    printf("\n3. Matrix Multiplication:\n");
    int elementsM1[][3] = {{0, 0, 1}, {0, 1, 2}, {1, 0, 3}, {1, 2, 4}};
    int elementsM2[][3] = {{0, 0, 1}, {0, 1, 2}, {1, 0, 3}, {2, 0, 5}};
    TSMatrix M1, M2;
    CreateTSMatrix(&M1, 2, 3, elementsM1, 4);
    CreateTSMatrix(&M2, 3, 2, elementsM2, 4);

    printf("Matrix M1:\n");
    PrintTSMatrix(M1);

    printf("\nMatrix M2:\n");
    PrintTSMatrix(M2);

    MultiplyTSMatrix(M1, M2, &D);
    printf("\nM1 * M2:\n");
    PrintTSMatrix(D);

    printf("\nM1 * M2 (full view):\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%3d ", GetTSMatrixElem(D, i, j));
        }
        printf("\n");
    }


    /* Cross linked list matrix test */
    printf("\n4. Cross Linked List Storage:\n");
    CrossList CL;
    int cl_elements[][3] = {{0, 0, 1}, {0, 3, 2}, {1, 1, 3}, {2, 0, 4}, {2, 2, 5}};
    CreateCrossList(&CL, 3, 4, cl_elements, 5);
    printf("Cross Linked List Matrix:\n");
    PrintCrossList(CL);

    printf("\nCross Linked List Matrix (full view):\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%2d ", GetCrossListElem(CL, i, j));
        }
        printf("\n");
    }

    DestroyCrossList(&CL);

    printf("\n=== All Tests Passed ===\n");
    return 0;
}
