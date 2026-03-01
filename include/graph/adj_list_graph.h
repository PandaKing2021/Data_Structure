#ifndef ADJ_LIST_GRAPH_H
#define ADJ_LIST_GRAPH_H

#define MAX_VEX 100

typedef struct EdgeNode {
    int adjvex;
    int weight;
    struct EdgeNode *next;
} EdgeNode;

typedef struct {
    int data;
    EdgeNode *firstedge;
} VertexNode;

typedef struct {
    VertexNode adjList[MAX_VEX];
    int numVertexes, numEdges;
} ALGraph;

void CreateALGraph(ALGraph *G);
void PrintALGraph(ALGraph G);
void DFS_ALG(ALGraph G, int v, int visited[]);
void BFS_ALG(ALGraph G, int v, int visited[]);

#endif
