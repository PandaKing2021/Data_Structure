/**
 * Multi-dimensional Array Storage Header
 *
 * Provides functions for calculating linear indices in multi-dimensional arrays
 * stored in contiguous memory. Supports both row-major and column-major ordering.
 *
 * Storage Orders:
 * - Row-major (C-style): Last dimension varies fastest
 *   Example: A[i][j][k] -> index = ((i*d2 + j)*d3 + k)
 *
 * - Column-major (Fortran-style): First dimension varies fastest
 *   Example: A[i][j][k] -> index = ((k*d2 + j)*d1 + i)
 *
 * Applications:
 * - Memory layout optimization
 * - Cache efficiency improvements
 * - Interfacing with different languages
 */

#ifndef MULTI_ARRAY_H
#define MULTI_ARRAY_H

/**
 * Calculate linear index for 2D array with row-major storage
 * Row-major: elements are stored row by row
 * Formula: index = i * cols + j
 *
 * @param rows Number of rows in the array
 * @param cols Number of columns in the array
 * @param i Row index (0-based)
 * @param j Column index (0-based)
 * @return Linear index in contiguous storage
 */
int RowMajorIndex(int rows, int cols, int i, int j);

/**
 * Calculate linear index for 2D array with column-major storage
 * Column-major: elements are stored column by column
 * Formula: index = j * rows + i
 *
 * @param rows Number of rows in the array
 * @param cols Number of columns in the array
 * @param i Row index (0-based)
 * @param j Column index (0-based)
 * @return Linear index in contiguous storage
 */
int ColMajorIndex(int rows, int cols, int i, int j);

/**
 * Calculate linear index for 3D array with row-major storage
 * Row-major: Last dimension (k) varies fastest
 * Formula: index = ((i * d2 + j) * d3 + k)
 *
 * @param d1 Size of first dimension
 * @param d2 Size of second dimension
 * @param d3 Size of third dimension
 * @param i Index in first dimension
 * @param j Index in second dimension
 * @param k Index in third dimension
 * @return Linear index in contiguous storage
 */
int RowMajorIndex3D(int d1, int d2, int d3, int i, int j, int k);

/**
 * Calculate linear index for 3D array with column-major storage
 * Column-major: First dimension (i) varies fastest
 * Formula: index = ((k * d2 + j) * d1 + i)
 *
 * @param d1 Size of first dimension
 * @param d2 Size of second dimension
 * @param d3 Size of third dimension
 * @param i Index in first dimension
 * @param j Index in second dimension
 * @param k Index in third dimension
 * @return Linear index in contiguous storage
 */
int ColMajorIndex3D(int d1, int d2, int d3, int i, int j, int k);

/**
 * Calculate linear index for general N-dimensional array with row-major storage
 * Row-major: Last dimension varies fastest
 * Formula: index = (...((indices[0]*dims[1] + indices[1])*dims[2] + ...)*dims[ndims-1] + indices[ndims-1])
 *
 * @param dims Array of dimension sizes
 * @param ndims Number of dimensions
 * @param indices Array of indices for each dimension
 * @return Linear index in contiguous storage
 */
int GeneralRowMajorIndex(int* dims, int ndims, int* indices);

/**
 * Calculate linear index for general N-dimensional array with column-major storage
 * Column-major: First dimension varies fastest
 * Formula: index = (...((indices[ndims-1]*dims[ndims-2] + indices[ndims-2])*dims[ndims-3] + ...)*dims[0] + indices[0])
 *
 * @param dims Array of dimension sizes
 * @param ndims Number of dimensions
 * @param indices Array of indices for each dimension
 * @return Linear index in contiguous storage
 */
int GeneralColMajorIndex(int* dims, int ndims, int* indices);

#endif
