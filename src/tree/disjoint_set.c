#include <stdio.h>
#include <stdlib.h>
#include "include/tree/disjoint_set.h"

void InitUFS(UFSTree *U, int n) {
    for (int i = 0; i < n; i++) {
        U->parent[i] = -1;
    }
}

int Find(UFSTree *U, int x) {
    while (U->parent[x] >= 0) {
        x = U->parent[x];
    }
    return x;
}

void Union(UFSTree *U, int x, int y) {
    int root1 = Find(U, x);
    int root2 = Find(U, y);
    if (root1 != root2) {
        U->parent[root1] += U->parent[root2];
        U->parent[root2] = root1;
    }
}
