#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#define MAX_SIZE 100

typedef struct {
    int parent[MAX_SIZE];
} UFSTree;

void InitUFS(UFSTree *U, int n);
int Find(UFSTree *U, int x);
void Union(UFSTree *U, int x, int y);

#endif
