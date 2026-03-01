#include "../../include/linear_list/multi_array.h"
#include <stdio.h>

// 获取二维数组行优先存储的线性索引
// 公式: index = i * cols + j
int RowMajorIndex(int rows, int cols, int i, int j) {
    return i * cols + j;
}

// 获取二维数组列优先存储的线性索引
// 公式: index = j * rows + i
int ColMajorIndex(int rows, int cols, int i, int j) {
    return j * rows + i;
}

// 获取三维数组行优先存储的线性索引
// 公式: index = ((i * d2) + j) * d3 + k
int RowMajorIndex3D(int d1, int d2, int d3, int i, int j, int k) {
    return ((i * d2) + j) * d3 + k;
}

// 获取三维数组列优先存储的线性索引
// 公式: index = ((k * d2) + j) * d1 + i
int ColMajorIndex3D(int d1, int d2, int d3, int i, int j, int k) {
    return ((k * d2) + j) * d1 + i;
}

// 获取一般多维数组行优先存储的线性索引
// 公式: index = ((i1 * d2 + i2) * d3 + i3) * ... + in
int GeneralRowMajorIndex(int* dims, int ndims, int* indices) {
    int index = 0;
    for (int i = 0; i < ndims; i++) {
        index = index * dims[i] + indices[i];
    }
    return index;
}

// 获取一般多维数组列优先存储的线性索引
// 公式: index = ((in * d(n-1) + i(n-1)) * d(n-2) + ...) + i1
int GeneralColMajorIndex(int* dims, int ndims, int* indices) {
    int index = 0;
    for (int i = ndims - 1; i >= 0; i--) {
        index = index * dims[i] + indices[i];
    }
    return index;
}
