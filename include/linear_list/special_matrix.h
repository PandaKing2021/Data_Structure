/**
 * Special Matrix Compression Storage Header
 *
 * Provides compressed storage representations for special types of matrices
 * that have many zero or redundant elements. Compression reduces memory usage
 * from O(n²) to O(n) for n×n matrices.
 *
 * Supported Matrix Types:
 *
 * 1. Symmetric Matrix: M[i][j] = M[j][i]
 *    Only store lower triangular part: n*(n+1)/2 elements
 *    Index: k = i*(i+1)/2 + j for i >= j
 *
 * 2. Lower Triangular Matrix: M[i][j] = 0 for j > i
 *    Only store lower triangular part: n*(n+1)/2 elements
 *    Index: k = i*(i+1)/2 + j for i >= j
 *
 * 3. Upper Triangular Matrix: M[i][j] = 0 for j < i
 *    Only store upper triangular part: n*(n+1)/2 elements
 *    Index: k = j*(j+1)/2 + i for j >= i
 *
 * 4. Tridiagonal Matrix: M[i][j] = 0 for |i-j| > 1
 *    Only store main diagonal and two adjacent diagonals: 3n-2 elements
 *    Index: k = 2*i + j for |i-j| <= 1
 */

#ifndef SPECIAL_MATRIX_H
#define SPECIAL_MATRIX_H

/**
 * Maximum matrix dimension supported
 */
#define MAX_SIZE 1000

/**
 * Symmetric Matrix Compressed Storage
 * Stores only the lower triangular portion including diagonal
 * Total elements: n*(n+1)/2
 */
typedef struct {
    int data[MAX_SIZE];  // Compressed one-dimensional array
    int n;              // Matrix order (dimension)
} SymmetricMatrix;

/**
 * Lower Triangular Matrix Compressed Storage
 * Stores only the lower triangular portion including diagonal
 * Total elements: n*(n+1)/2
 */
typedef struct {
    int data[MAX_SIZE];  // Compressed one-dimensional array
    int n;              // Matrix order (dimension)
} LowerTriangularMatrix;

/**
 * Upper Triangular Matrix Compressed Storage
 * Stores only the upper triangular portion including diagonal
 * Total elements: n*(n+1)/2
 */
typedef struct {
    int data[MAX_SIZE];  // Compressed one-dimensional array
    int n;              // Matrix order (dimension)
} UpperTriangularMatrix;

/**
 * Tridiagonal Matrix Compressed Storage
 * Stores only main diagonal and two adjacent diagonals
 * Total elements: 3n - 2
 * Storage order: lower diagonal, main diagonal, upper diagonal
 */
typedef struct {
    int data[MAX_SIZE];  // Compressed one-dimensional array
    int n;              // Matrix order (dimension)
} TridiagonalMatrix;

// ============================================================================
// Symmetric Matrix Operations
// ============================================================================

/**
 * Initialize a symmetric matrix
 * @param M Pointer to matrix to initialize
 * @param n Matrix dimension
 */
void InitSymmetricMatrix(SymmetricMatrix *M, int n);

/**
 * Get element value at position (i, j)
 * Uses symmetry: M[i][j] = M[j][i]
 * @param M Symmetric matrix
 * @param i Row index (0-based)
 * @param j Column index (0-based)
 * @return Element value
 */
int GetSymmetricElem(SymmetricMatrix M, int i, int j);

/**
 * Set element value at position (i, j)
 * Automatically sets both M[i][j] and M[j][i] due to symmetry
 * @param M Pointer to symmetric matrix
 * @param i Row index (0-based)
 * @param j Column index (0-based)
 * @param value Value to set
 */
void SetSymmetricElem(SymmetricMatrix *M, int i, int j, int value);

// ============================================================================
// Lower Triangular Matrix Operations
// ============================================================================

/**
 * Initialize a lower triangular matrix
 * @param M Pointer to matrix to initialize
 * @param n Matrix dimension
 */
void InitLowerTriangularMatrix(LowerTriangularMatrix *M, int n);

/**
 * Get element value at position (i, j)
 * Returns 0 for elements above diagonal (j > i)
 * @param M Lower triangular matrix
 * @param i Row index (0-based)
 * @param j Column index (0-based)
 * @return Element value (0 if j > i)
 */
int GetLowerTriangularElem(LowerTriangularMatrix M, int i, int j);

/**
 * Set element value at position (i, j)
 * Only allows setting elements on or below diagonal (i >= j)
 * @param M Pointer to lower triangular matrix
 * @param i Row index (0-based)
 * @param j Column index (0-based)
 * @param value Value to set
 */
void SetLowerTriangularElem(LowerTriangularMatrix *M, int i, int j, int value);

// ============================================================================
// Upper Triangular Matrix Operations
// ============================================================================

/**
 * Initialize an upper triangular matrix
 * @param M Pointer to matrix to initialize
 * @param n Matrix dimension
 */
void InitUpperTriangularMatrix(UpperTriangularMatrix *M, int n);

/**
 * Get element value at position (i, j)
 * Returns 0 for elements below diagonal (i > j)
 * @param M Upper triangular matrix
 * @param i Row index (0-based)
 * @param j Column index (0-based)
 * @return Element value (0 if i > j)
 */
int GetUpperTriangularElem(UpperTriangularMatrix M, int i, int j);

/**
 * Set element value at position (i, j)
 * Only allows setting elements on or above diagonal (j >= i)
 * @param M Pointer to upper triangular matrix
 * @param i Row index (0-based)
 * @param j Column index (0-based)
 * @param value Value to set
 */
void SetUpperTriangularElem(UpperTriangularMatrix *M, int i, int j, int value);

// ============================================================================
// Tridiagonal Matrix Operations
// ============================================================================

/**
 * Initialize a tridiagonal matrix
 * @param M Pointer to matrix to initialize
 * @param n Matrix dimension
 */
void InitTridiagonalMatrix(TridiagonalMatrix *M, int n);

/**
 * Get element value at position (i, j)
 * Returns 0 for elements not on main or adjacent diagonals
 * @param M Tridiagonal matrix
 * @param i Row index (0-based)
 * @param j Column index (0-based)
 * @return Element value (0 if |i-j| > 1)
 */
int GetTridiagonalElem(TridiagonalMatrix M, int i, int j);

/**
 * Set element value at position (i, j)
 * Only allows setting elements on main or adjacent diagonals (|i-j| <= 1)
 * @param M Pointer to tridiagonal matrix
 * @param i Row index (0-based)
 * @param j Column index (0-based)
 * @param value Value to set
 */
void SetTridiagonalElem(TridiagonalMatrix *M, int i, int j, int value);

#endif
