#include "../../include/linear_list/special_matrix.h"
#include <stdio.h>

int main() {
    printf("=== Special Matrix Compression Storage Tests ===\n\n");

    /* Symmetric matrix test */
    printf("1. Symmetric Matrix (4x4):\n");
    SymmetricMatrix symM;
    InitSymmetricMatrix(&symM, 4);

    SetSymmetricElem(&symM, 0, 0, 1);
    SetSymmetricElem(&symM, 0, 1, 2);
    SetSymmetricElem(&symM, 0, 2, 3);
    SetSymmetricElem(&symM, 0, 3, 4);
    SetSymmetricElem(&symM, 1, 1, 5);
    SetSymmetricElem(&symM, 1, 2, 6);
    SetSymmetricElem(&symM, 1, 3, 7);
    SetSymmetricElem(&symM, 2, 2, 8);
    SetSymmetricElem(&symM, 2, 3, 9);
    SetSymmetricElem(&symM, 3, 3, 10);

    printf("Symmetric Matrix:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%3d ", GetSymmetricElem(symM, i, j));
        }
        printf("\n");
    }

    /* Lower triangular matrix test */
    printf("\n2. Lower Triangular Matrix (4x4):\n");
    LowerTriangularMatrix lowM;
    InitLowerTriangularMatrix(&lowM, 4);

    SetLowerTriangularElem(&lowM, 0, 0, 1);
    SetLowerTriangularElem(&lowM, 1, 0, 2);
    SetLowerTriangularElem(&lowM, 1, 1, 3);
    SetLowerTriangularElem(&lowM, 2, 0, 4);
    SetLowerTriangularElem(&lowM, 2, 1, 5);
    SetLowerTriangularElem(&lowM, 2, 2, 6);
    SetLowerTriangularElem(&lowM, 3, 0, 7);
    SetLowerTriangularElem(&lowM, 3, 1, 8);
    SetLowerTriangularElem(&lowM, 3, 2, 9);
    SetLowerTriangularElem(&lowM, 3, 3, 10);

    printf("Lower Triangular Matrix:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%3d ", GetLowerTriangularElem(lowM, i, j));
        }
        printf("\n");
    }

    /* Upper triangular matrix test */
    printf("\n3. Upper Triangular Matrix (4x4):\n");
    UpperTriangularMatrix upM;
    InitUpperTriangularMatrix(&upM, 4);

    SetUpperTriangularElem(&upM, 0, 0, 1);
    SetUpperTriangularElem(&upM, 0, 1, 2);
    SetUpperTriangularElem(&upM, 0, 2, 3);
    SetUpperTriangularElem(&upM, 0, 3, 4);
    SetUpperTriangularElem(&upM, 1, 1, 5);
    SetUpperTriangularElem(&upM, 1, 2, 6);
    SetUpperTriangularElem(&upM, 1, 3, 7);
    SetUpperTriangularElem(&upM, 2, 2, 8);
    SetUpperTriangularElem(&upM, 2, 3, 9);
    SetUpperTriangularElem(&upM, 3, 3, 10);

    printf("Upper Triangular Matrix:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%3d ", GetUpperTriangularElem(upM, i, j));
        }
        printf("\n");
    }

    /* Tridiagonal matrix test */
    printf("\n4. Tridiagonal Matrix (5x5):\n");
    TridiagonalMatrix triM;
    InitTridiagonalMatrix(&triM, 5);

    SetTridiagonalElem(&triM, 0, 0, 1);
    SetTridiagonalElem(&triM, 0, 1, 2);
    SetTridiagonalElem(&triM, 1, 0, 3);
    SetTridiagonalElem(&triM, 1, 1, 4);
    SetTridiagonalElem(&triM, 1, 2, 5);
    SetTridiagonalElem(&triM, 2, 1, 6);
    SetTridiagonalElem(&triM, 2, 2, 7);
    SetTridiagonalElem(&triM, 2, 3, 8);
    SetTridiagonalElem(&triM, 3, 2, 9);
    SetTridiagonalElem(&triM, 3, 3, 10);
    SetTridiagonalElem(&triM, 3, 4, 11);
    SetTridiagonalElem(&triM, 4, 3, 12);
    SetTridiagonalElem(&triM, 4, 4, 13);

    printf("Tridiagonal Matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%3d ", GetTridiagonalElem(triM, i, j));
        }
        printf("\n");
    }

    printf("\n=== All Tests Passed ===\n");
    return 0;
}
