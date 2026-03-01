#include "../../include/linear_list/sparse_matrix.h"
#include <stdio.h>
#include <stdlib.h>

/* ==================== Triplet (Sparse Matrix) Operations ==================== */

/**
 * Initialize a Triplet sparse matrix structure.
 * @param M Pointer to the TSMatrix structure
 */
void InitTSMatrix(TSMatrix *M) {
    M->rows = M->cols = M->num = 0;
}

/**
 * Create a Triplet sparse matrix from an array of elements.
 * @param M Pointer to the TSMatrix structure
 * @param rows Number of rows
 * @param cols Number of columns
 * @param elements Array of (row, col, value) triplets
 * @param n Number of non-zero elements
 * @return 1 on success
 */
int CreateTSMatrix(TSMatrix *M, int rows, int cols, int elements[][3], int n) {
    M->rows = rows;
    M->cols = cols;
    M->num = n;

    for (int k = 0; k < n; k++) {
        M->data[k].i = elements[k][0];
        M->data[k].j = elements[k][1];
        M->data[k].v = elements[k][2];
    }

    return 1;
}

/**
 * Get an element from the Triplet matrix.
 * @param M The TSMatrix structure
 * @param i Row index
 * @param j Column index
 * @return The element value, or 0 if not found
 */
int GetTSMatrixElem(TSMatrix M, int i, int j) {
    for (int k = 0; k < M.num; k++) {
        if (M.data[k].i == i && M.data[k].j == j) {
            return M.data[k].v;
        }
    }
    return 0;
}

/**
 * Set an element in the Triplet matrix.
 * @param M Pointer to the TSMatrix structure
 * @param i Row index
 * @param j Column index
 * @param value The value to set
 */
void SetTSMatrixElem(TSMatrix *M, int i, int j, int value) {
    for (int k = 0; k < M->num; k++) {
        if (M->data[k].i == i && M->data[k].j == j) {
            M->data[k].v = value;
            return;
        }
    }

    if (value != 0 && M->num < MAX_SIZE) {
        M->data[M->num].i = i;
        M->data[M->num].j = j;
        M->data[M->num].v = value;
        M->num++;
    }
}

/**
 * Transpose a Triplet matrix.
 * @param M Source matrix
 * @param T Pointer to store the transposed matrix
 */
void TransposeTSMatrix(TSMatrix M, TSMatrix *T) {
    T->rows = M.cols;
    T->cols = M.rows;
    T->num = M.num;

    if (T->num > 0) {
        int q = 0;
        for (int col = 0; col < M.cols; col++) {
            for (int p = 0; p < M.num; p++) {
                if (M.data[p].j == col) {
                    T->data[q].i = M.data[p].j;
                    T->data[q].j = M.data[p].i;
                    T->data[q].v = M.data[p].v;
                    q++;
                }
            }
        }
    }
}

/**
 * Print the Triplet matrix in triplet form.
 * @param M The TSMatrix structure to print
 */
void PrintTSMatrix(TSMatrix M) {
    printf("TSMatrix (%d x %d, %d non-zero elements):\n", M.rows, M.cols, M.num);
    for (int k = 0; k < M.num; k++) {
        printf("(%d, %d) = %d\n", M.data[k].i, M.data[k].j, M.data[k].v);
    }
}

/**
 * Add two Triplet matrices.
 * @param A First matrix
 * @param B Second matrix
 * @param C Pointer to store the result
 * @return 1 on success, 0 if matrices have different dimensions
 */
int AddTSMatrix(TSMatrix A, TSMatrix B, TSMatrix *C) {
    if (A.rows != B.rows || A.cols != B.cols) {
        return 0;
    }

    C->rows = A.rows;
    C->cols = A.cols;
    C->num = 0;

    int pa = 0, pb = 0;

    while (pa < A.num && pb < B.num) {
        if (A.data[pa].i < B.data[pb].i ||
            (A.data[pa].i == B.data[pb].i && A.data[pa].j < B.data[pb].j)) {
            C->data[C->num++] = A.data[pa++];
        } else if (A.data[pa].i > B.data[pb].i ||
                   (A.data[pa].i == B.data[pb].i && A.data[pa].j > B.data[pb].j)) {
            C->data[C->num++] = B.data[pb++];
        } else {
            int sum = A.data[pa].v + B.data[pb].v;
            if (sum != 0) {
                C->data[C->num].i = A.data[pa].i;
                C->data[C->num].j = A.data[pa].j;
                C->data[C->num++].v = sum;
            }
            pa++;
            pb++;
        }
    }

    while (pa < A.num) {
        C->data[C->num++] = A.data[pa++];
    }
    while (pb < B.num) {
        C->data[C->num++] = B.data[pb++];
    }

    return 1;
}

/**
 * Multiply two Triplet matrices.
 * @param A First matrix
 * @param B Second matrix
 * @param C Pointer to store the result
 * @return 1 on success, 0 if matrices are incompatible for multiplication
 */
int MultiplyTSMatrix(TSMatrix A, TSMatrix B, TSMatrix *C) {
    if (A.cols != B.rows) {
        return 0;
    }

    C->rows = A.rows;
    C->cols = B.cols;
    C->num = 0;

    int temp[MAX_SIZE] = {0};

    for (int i = 0; i < A.rows; i++) {
        for (int k = 0; k < B.cols; k++) {
            temp[k] = 0;
        }

        for (int pa = 0; pa < A.num; pa++) {
            if (A.data[pa].i == i) {
                int j = A.data[pa].j;
                for (int pb = 0; pb < B.num; pb++) {
                    if (B.data[pb].i == j) {
                        int k = B.data[pb].j;
                        temp[k] += A.data[pa].v * B.data[pb].v;
                    }
                }
            }
        }

        for (int k = 0; k < B.cols; k++) {
            if (temp[k] != 0) {
                C->data[C->num].i = i;
                C->data[C->num].j = k;
                C->data[C->num++].v = temp[k];
            }
        }
    }

    return 1;
}

/* ==================== Cross List (Orthogonal List) Operations ==================== */

/**
 * Initialize a Cross List sparse matrix structure.
 * @param M Pointer to the CrossList structure
 * @param rows Number of rows
 * @param cols Number of columns
 */
void InitCrossList(CrossList *M, int rows, int cols) {
    M->rows = rows;
    M->cols = cols;
    M->num = 0;

    M->rhead = (OLink *)malloc(rows * sizeof(OLink));
    M->chead = (OLink *)malloc(cols * sizeof(OLink));

    for (int i = 0; i < rows; i++) {
        M->rhead[i] = NULL;
    }
    for (int j = 0; j < cols; j++) {
        M->chead[j] = NULL;
    }
}

/**
 * Create a Cross List sparse matrix from an array of elements.
 * @param M Pointer to the CrossList structure
 * @param rows Number of rows
 * @param cols Number of columns
 * @param elements Array of (row, col, value) triplets
 * @param n Number of non-zero elements
 * @return 1 on success
 */
int CreateCrossList(CrossList *M, int rows, int cols, int elements[][3], int n) {
    InitCrossList(M, rows, cols);

    for (int k = 0; k < n; k++) {
        int i = elements[k][0];
        int j = elements[k][1];
        int v = elements[k][2];

        OLNode *p = (OLNode *)malloc(sizeof(OLNode));
        p->i = i;
        p->j = j;
        p->v = v;
        p->right = p->down = NULL;

        if (M->rhead[i] == NULL || M->rhead[i]->j > j) {
            p->right = M->rhead[i];
            M->rhead[i] = p;
        } else {
            OLNode *q = M->rhead[i];
            while (q->right && q->right->j < j) {
                q = q->right;
            }
            p->right = q->right;
            q->right = p;
        }

        if (M->chead[j] == NULL || M->chead[j]->i > i) {
            p->down = M->chead[j];
            M->chead[j] = p;
        } else {
            OLNode *q = M->chead[j];
            while (q->down && q->down->i < i) {
                q = q->down;
            }
            p->down = q->down;
            q->down = p;
        }

        M->num++;
    }

    return 1;
}

/**
 * Get an element from the Cross List matrix.
 * @param M The CrossList structure
 * @param i Row index
 * @param j Column index
 * @return The element value, or 0 if not found
 */
int GetCrossListElem(CrossList M, int i, int j) {
    OLNode *p = M.rhead[i];
    while (p && p->j <= j) {
        if (p->j == j) {
            return p->v;
        }
        p = p->right;
    }
    return 0;
}

/**
 * Set an element in the Cross List matrix.
 * @param M Pointer to the CrossList structure
 * @param i Row index
 * @param j Column index
 * @param value The value to set
 */
void SetCrossListElem(CrossList *M, int i, int j, int value) {
    OLNode *p = M->rhead[i];

    if (value != 0) {
        OLNode *new_node = (OLNode *)malloc(sizeof(OLNode));
        new_node->i = i;
        new_node->j = j;
        new_node->v = value;
        new_node->right = new_node->down = NULL;

        if (p == NULL || p->j > j) {
            new_node->right = p;
            M->rhead[i] = new_node;
        } else {
            while (p->right && p->right->j < j) {
                p = p->right;
            }
            new_node->right = p->right;
            p->right = new_node;
        }

        OLNode *col_p = M->chead[j];
        if (col_p == NULL || col_p->i > i) {
            new_node->down = col_p;
            M->chead[j] = new_node;
        } else {
            while (col_p->down && col_p->down->i < i) {
                col_p = col_p->down;
            }
            new_node->down = col_p->down;
            col_p->down = new_node;
        }

        M->num++;
    }
}

/**
 * Print the Cross List matrix in triplet form.
 * @param M The CrossList structure to print
 */
void PrintCrossList(CrossList M) {
    printf("CrossList (%d x %d, %d non-zero elements):\n", M.rows, M.cols, M.num);
    for (int i = 0; i < M.rows; i++) {
        OLNode *p = M.rhead[i];
        while (p) {
            printf("(%d, %d) = %d\n", p->i, p->j, p->v);
            p = p->right;
        }
    }
}

/**
 * Destroy the Cross List and free all allocated memory.
 * @param M Pointer to the CrossList structure to destroy
 */
void DestroyCrossList(CrossList *M) {
    for (int i = 0; i < M->rows; i++) {
        OLNode *p = M->rhead[i];
        while (p) {
            OLNode *temp = p;
            p = p->right;
            free(temp);
        }
    }
    free(M->rhead);
    free(M->chead);
    M->rhead = M->chead = NULL;
    M->num = 0;
}
