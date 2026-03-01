#include <stdio.h>
#include <stdlib.h>
#include "include/graph/adj_list_graph.h"

void CreateALGraph(ALGraph *G) {
    printf("Enter number of vertices and edges: ");
    scanf("%d%d", &G->numVertexes, &G->numEdges);
    printf("Enter vertices: ");
    for (int i = 0; i < G->numVertexes; i++) {
        scanf("%d", &G->adjList[i].data);
        G->adjList[i].firstedge = NULL;
    }
    printf("Enter edges (v1 v2 weight):\n");
    for (int k = 0; k < G->numEdges; k++) {
        int v1, v2, w;
        scanf("%d%d%d", &v1, &v2, &w);
        int i = -1, j = -1;
        for (int m = 0; m < G->numVertexes; m++) {
            if (G->adjList[m].data == v1) i = m;
            if (G->adjList[m].data == v2) j = m;
        }
        if (i != -1 && j != -1) {
            EdgeNode *p = (EdgeNode *)malloc(sizeof(EdgeNode));
            p->adjvex = j;
            p->weight = w;
            p->next = G->adjList[i].firstedge;
            G->adjList[i].firstedge = p;
            p = (EdgeNode *)malloc(sizeof(EdgeNode));
            p->adjvex = i;
            p->weight = w;
            p->next = G->adjList[j].firstedge;
            G->adjList[j].firstedge = p;
        }
    }
}

void PrintALGraph(ALGraph G) {
    printf("Adjacency List:\n");
    for (int i = 0; i < G.numVertexes; i++) {
        printf("%d -> ", G.adjList[i].data);
        EdgeNode *p = G.adjList[i].firstedge;
        while (p) {
            printf("%d(%d) ", G.adjList[p->adjvex].data, p->weight);
            p = p->next;
        }
        printf("\n");
    }
}

void DFS_ALG(ALGraph G, int v, int visited[]) {
    printf("%d ", G.adjList[v].data);
    visited[v] = 1;
    EdgeNode *p = G.adjList[v].firstedge;
    while (p) {
        if (!visited[p->adjvex]) {
            DFS_ALG(G, p->adjvex, visited);
        }
        p = p->next;
    }
}

void BFS_ALG(ALGraph G, int v, int visited[]) {
    int queue[MAX_VEX];
    int front = 0, rear = 0;
    printf("%d ", G.adjList[v].data);
    visited[v] = 1;
    queue[rear++] = v;
    while (front < rear) {
        v = queue[front++];
        EdgeNode *p = G.adjList[v].firstedge;
        while (p) {
            if (!visited[p->adjvex]) {
                printf("%d ", G.adjList[p->adjvex].data);
                visited[p->adjvex] = 1;
                queue[rear++] = p->adjvex;
            }
            p = p->next;
        }
    }
}
