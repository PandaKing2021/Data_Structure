#include "../../include/linear_list/special_matrix.h"
#include <stdio.h>

/**
 * Initialize a Symmetric Matrix structure.
 * @param M Pointer to the SymmetricMatrix structure
 * @param n Dimension of the matrix (n x n)
 */
void InitSymmetricMatrix(SymmetricMatrix *M, int n) {
    M->n = n;
    for (int i = 0; i < n * (n + 1) / 2; i++) {
        M->data[i] = 0;
    }
}

/**
 * Get an element from the Symmetric Matrix.
 * Index mapping: k = i*(i+1)/2 + j (i >= j), k = j*(j+1)/2 + i (i < j)
 * @param M The SymmetricMatrix structure
 * @param i Row index
 * @param j Column index
 * @return The element value
 */
int GetSymmetricElem(SymmetricMatrix M, int i, int j) {
    if (i >= j) {
        return M.data[i * (i + 1) / 2 + j];
    } else {
        return M.data[j * (j + 1) / 2 + i];
    }
}

/**
 * Set an element in the Symmetric Matrix.
 * @param M Pointer to the SymmetricMatrix structure
 * @param i Row index
 * @param j Column index
 * @param value The value to set
 */
void SetSymmetricElem(SymmetricMatrix *M, int i, int j, int value) {
    if (i >= j) {
        M->data[i * (i + 1) / 2 + j] = value;
    } else {
        M->data[j * (j + 1) / 2 + i] = value;
    }
}

/**
 * Initialize a Lower Triangular Matrix structure.
 * @param M Pointer to the LowerTriangularMatrix structure
 * @param n Dimension of the matrix (n x n)
 */
void InitLowerTriangularMatrix(LowerTriangularMatrix *M, int n) {
    M->n = n;
    for (int i = 0; i < n * (n + 1) / 2; i++) {
        M->data[i] = 0;
    }
}

/**
 * Get an element from the Lower Triangular Matrix.
 * Index mapping: k = i*(i+1)/2 + j (i >= j), returns 0 if i < j
 * @param M The LowerTriangularMatrix structure
 * @param i Row index
 * @param j Column index
 * @return The element value
 */
int GetLowerTriangularElem(LowerTriangularMatrix M, int i, int j) {
    if (i >= j) {
        return M.data[i * (i + 1) / 2 + j];
    } else {
        return 0;
    }
}

/**
 * Set an element in the Lower Triangular Matrix.
 * Only stores elements where i >= j.
 * @param M Pointer to the LowerTriangularMatrix structure
 * @param i Row index
 * @param j Column index
 * @param value The value to set
 */
void SetLowerTriangularElem(LowerTriangularMatrix *M, int i, int j, int value) {
    if (i >= j) {
        M->data[i * (i + 1) / 2 + j] = value;
    }
}

/**
 * Initialize an Upper Triangular Matrix structure.
 * @param M Pointer to the UpperTriangularMatrix structure
 * @param n Dimension of the matrix (n x n)
 */
void InitUpperTriangularMatrix(UpperTriangularMatrix *M, int n) {
    M->n = n;
    for (int i = 0; i < n * (n + 1) / 2; i++) {
        M->data[i] = 0;
    }
}

/**
 * Get an element from the Upper Triangular Matrix (column-major storage).
 * Index mapping: k = j*(j+1)/2 + i (j >= i), returns 0 if j < i
 * @param M The UpperTriangularMatrix structure
 * @param i Row index
 * @param j Column index
 * @return The element value
 */
int GetUpperTriangularElem(UpperTriangularMatrix M, int i, int j) {
    if (j >= i) {
        return M.data[j * (j + 1) / 2 + i];
    } else {
        return 0;
    }
}

/**
 * Set an element in the Upper Triangular Matrix.
 * Only stores elements where j >= i.
 * @param M Pointer to the UpperTriangularMatrix structure
 * @param i Row index
 * @param j Column index
 * @param value The value to set
 */
void SetUpperTriangularElem(UpperTriangularMatrix *M, int i, int j, int value) {
    if (j >= i) {
        M->data[j * (j + 1) / 2 + i] = value;
    }
}

/**
 * Initialize a Tridiagonal Matrix structure.
 * @param M Pointer to the TridiagonalMatrix structure
 * @param n Dimension of the matrix (n x n)
 */
void InitTridiagonalMatrix(TridiagonalMatrix *M, int n) {
    M->n = n;
    for (int i = 0; i < 3 * n - 2; i++) {
        M->data[i] = 0;
    }
}

/**
 * Get an element from the Tridiagonal Matrix.
 * Index mapping: k = 2*i + j (|i-j| <= 1), returns 0 otherwise
 * @param M The TridiagonalMatrix structure
 * @param i Row index
 * @param j Column index
 * @return The element value
 */
int GetTridiagonalElem(TridiagonalMatrix M, int i, int j) {
    if ((i == j) || (i == j + 1) || (j == i + 1)) {
        if (i == j + 1) {
            return M.data[2 * i + j - 1];
        } else if (j == i + 1) {
            return M.data[2 * i + j - 1];
        } else {
            return M.data[2 * i];
        }
    }
    return 0;
}

/**
 * Set an element in the Tridiagonal Matrix.
 * Only stores elements where |i-j| <= 1.
 * @param M Pointer to the TridiagonalMatrix structure
 * @param i Row index
 * @param j Column index
 * @param value The value to set
 */
void SetTridiagonalElem(TridiagonalMatrix *M, int i, int j, int value) {
    if ((i == j) || (i == j + 1) || (j == i + 1)) {
        if (i == j) {
            M->data[2 * i] = value;
        } else {
            M->data[2 * i + j - 1] = value;
        }
    }
}
