#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

#define MAX_VEX 100

typedef struct {
    int vexs[MAX_VEX];
    int arc[MAX_VEX][MAX_VEX];
    int numVertexes, numEdges;
} MGraph;

void CreateMGraph(MGraph *G);
void PrintMGraph(MGraph G);
void DFS(MGraph G, int v, int visited[]);
void BFS(MGraph G, int v, int visited[]);

void Prim(MGraph G);
void Kruskal(MGraph G);
void Dijkstra(MGraph G, int v);
void Floyd(MGraph G);
void TopologicalSort(MGraph G);
void CriticalPath(MGraph G);

#endif
