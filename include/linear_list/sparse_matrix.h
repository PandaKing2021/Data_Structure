/**
 * Sparse Matrix Storage Header
 *
 * Provides efficient storage representations for sparse matrices (matrices
 * with most elements equal to zero). Two common representations are implemented:
 *
 * 1. Triplet (Coordinate) Format:
 *    - Stores only non-zero elements as (row, col, value) tuples
 *    - Simple and memory-efficient for sparse matrices
 *    - Good for matrix construction and simple operations
 *
 * 2. Orthogonal List (Cross List) Format:
 *    - Linked structure with row and column lists
 *    - Efficient for dynamic matrices with frequent insertions/deletions
 *    - Supports faster matrix operations like transpose and multiplication
 *
 * Advantages over dense storage:
 * - Memory efficiency: O(non-zero elements) vs O(n*m)
 * - Faster operations on sparse data
 * - Scalable to large sparse matrices
 */

#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

/**
 * Maximum number of non-zero elements supported
 */
#define MAX_SIZE 10000

/**
 * Triple Structure
 * Represents a single non-zero element in the matrix
 */
typedef struct {
    int i;      // Row index (0-based)
    int j;      // Column index (0-based)
    int v;      // Element value
} Triple;

/**
 * Triplet Sequential Matrix (TSMatrix)
 * Sparse matrix stored as an array of triples sorted by row, then column
 */
typedef struct {
    Triple data[MAX_SIZE];  // Array of non-zero element triples
    int rows;              // Number of rows in the matrix
    int cols;              // Number of columns in the matrix
    int num;               // Number of non-zero elements
} TSMatrix;

/**
 * Orthogonal List Node (OLNode)
 * Node in the cross-linked list structure
 */
typedef struct OLNode {
    int i, j;                      // Row and column indices
    int v;                         // Element value
    struct OLNode *right, *down;   // Pointers to next element in row and column
} OLNode, *OLink;

/**
 * Cross Linked List Matrix (CrossList)
 * Sparse matrix stored as orthogonal linked lists
 * Each row and column has its own linked list of non-zero elements
 */
typedef struct {
    OLink *rhead;      // Array of row head pointers
    OLink *chead;      // Array of column head pointers
    int rows;          // Number of rows in the matrix
    int cols;          // Number of columns in the matrix
    int num;           // Number of non-zero elements
} CrossList;

// ============================================================================
// Triplet Matrix Operations
// ============================================================================

/**
 * Initialize an empty triplet matrix
 * @param M Pointer to matrix to initialize
 */
void InitTSMatrix(TSMatrix *M);

/**
 * Create a triplet matrix from element array
 * @param M Pointer to matrix to create
 * @param rows Number of rows
 * @param cols Number of columns
 * @param elements Array of [row, col, value] triples
 * @param n Number of non-zero elements
 * @return 1 on success, 0 on failure
 */
int CreateTSMatrix(TSMatrix *M, int rows, int cols, int elements[][3], int n);

/**
 * Get element value at position (i, j)
 * @param M Matrix to query
 * @param i Row index
 * @param j Column index
 * @return Element value, or 0 if element is zero or position invalid
 */
int GetTSMatrixElem(TSMatrix M, int i, int j);

/**
 * Set element value at position (i, j)
 * Inserts or updates a non-zero element
 * @param M Pointer to matrix
 * @param i Row index
 * @param j Column index
 * @param value Value to set
 */
void SetTSMatrixElem(TSMatrix *M, int i, int j, int value);

/**
 * Transpose the matrix (swap rows and columns)
 * @param M Source matrix
 * @param T Destination matrix for transposed result
 */
void TransposeTSMatrix(TSMatrix M, TSMatrix *T);

/**
 * Print the triplet matrix
 * @param M Matrix to print
 */
void PrintTSMatrix(TSMatrix M);

/**
 * Add two triplet matrices
 * @param A First matrix
 * @param B Second matrix
 * @param C Result matrix (A + B)
 * @return 1 on success, 0 on failure (dimension mismatch)
 */
int AddTSMatrix(TSMatrix A, TSMatrix B, TSMatrix *C);

/**
 * Multiply two triplet matrices
 * @param A First matrix (m x n)
 * @param B Second matrix (n x p)
 * @param C Result matrix (m x p)
 * @return 1 on success, 0 on failure (dimension mismatch)
 */
int MultiplyTSMatrix(TSMatrix A, TSMatrix B, TSMatrix *C);

// ============================================================================
// Cross Linked List Matrix Operations
// ============================================================================

/**
 * Initialize an empty cross linked list matrix
 * @param M Pointer to matrix to initialize
 * @param rows Number of rows
 * @param cols Number of columns
 */
void InitCrossList(CrossList *M, int rows, int cols);

/**
 * Create a cross linked list matrix from element array
 * @param M Pointer to matrix to create
 * @param rows Number of rows
 * @param cols Number of columns
 * @param elements Array of [row, col, value] triples
 * @param n Number of non-zero elements
 * @return 1 on success, 0 on failure
 */
int CreateCrossList(CrossList *M, int rows, int cols, int elements[][3], int n);

/**
 * Get element value at position (i, j)
 * @param M Matrix to query
 * @param i Row index
 * @param j Column index
 * @return Element value, or 0 if element is zero or position invalid
 */
int GetCrossListElem(CrossList M, int i, int j);

/**
 * Set element value at position (i, j)
 * Inserts or updates a non-zero element
 * @param M Pointer to matrix
 * @param i Row index
 * @param j Column index
 * @param value Value to set
 */
void SetCrossListElem(CrossList *M, int i, int j, int value);

/**
 * Print the cross linked list matrix
 * @param M Matrix to print
 */
void PrintCrossList(CrossList M);

/**
 * Destroy the cross linked list matrix and free memory
 * @param M Pointer to matrix to destroy
 */
void DestroyCrossList(CrossList *M);

#endif
