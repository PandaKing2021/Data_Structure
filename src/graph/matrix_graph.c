#include <stdio.h>
#include <stdlib.h>
#include "include/graph/matrix_graph.h"

void CreateMGraph(MGraph *G) {
    printf("Enter number of vertices and edges: ");
    scanf("%d%d", &G->numVertexes, &G->numEdges);
    printf("Enter vertices: ");
    for (int i = 0; i < G->numVertexes; i++) {
        scanf("%d", &G->vexs[i]);
    }
    for (int i = 0; i < G->numVertexes; i++) {
        for (int j = 0; j < G->numVertexes; j++) {
            G->arc[i][j] = 0;
        }
    }
    printf("Enter edges (v1 v2 weight):\n");
    for (int k = 0; k < G->numEdges; k++) {
        int v1, v2, w;
        scanf("%d%d%d", &v1, &v2, &w);
        int i = -1, j = -1;
        for (int m = 0; m < G->numVertexes; m++) {
            if (G->vexs[m] == v1) i = m;
            if (G->vexs[m] == v2) j = m;
        }
        if (i != -1 && j != -1) {
            G->arc[i][j] = w;
            G->arc[j][i] = w;
        }
    }
}

void PrintMGraph(MGraph G) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < G.numVertexes; i++) {
        for (int j = 0; j < G.numVertexes; j++) {
            printf("%3d ", G.arc[i][j]);
        }
        printf("\n");
    }
}

void DFS(MGraph G, int v, int visited[]) {
    printf("%d ", G.vexs[v]);
    visited[v] = 1;
    for (int i = 0; i < G.numVertexes; i++) {
        if (G.arc[v][i] && !visited[i]) {
            DFS(G, i, visited);
        }
    }
}

void BFS(MGraph G, int v, int visited[]) {
    int queue[MAX_VEX];
    int front = 0, rear = 0;
    printf("%d ", G.vexs[v]);
    visited[v] = 1;
    queue[rear++] = v;
    while (front < rear) {
        v = queue[front++];
        for (int i = 0; i < G.numVertexes; i++) {
            if (G.arc[v][i] && !visited[i]) {
                printf("%d ", G.vexs[i]);
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}

void Prim(MGraph G) {
    int lowcost[MAX_VEX], adjvex[MAX_VEX];
    int i, j, min, k;
    for (i = 1; i < G.numVertexes; i++) {
        lowcost[i] = G.arc[0][i];
        adjvex[i] = 0;
    }
    lowcost[0] = 0;
    for (i = 1; i < G.numVertexes; i++) {
        min = 9999;
        k = 0;
        for (j = 1; j < G.numVertexes; j++) {
            if (lowcost[j] && lowcost[j] < min) {
                min = lowcost[j];
                k = j;
            }
        }
        printf("Edge: %d - %d, Weight: %d\n", G.vexs[adjvex[k]], G.vexs[k], min);
        lowcost[k] = 0;
        for (j = 1; j < G.numVertexes; j++) {
            if (lowcost[j] && G.arc[k][j] < lowcost[j]) {
                lowcost[j] = G.arc[k][j];
                adjvex[j] = k;
            }
        }
    }
}

void Kruskal(MGraph G) {
    int edges[MAX_VEX * MAX_VEX][3];
    int k = 0;
    for (int i = 0; i < G.numVertexes; i++) {
        for (int j = i + 1; j < G.numVertexes; j++) {
            if (G.arc[i][j]) {
                edges[k][0] = i;
                edges[k][1] = j;
                edges[k][2] = G.arc[i][j];
                k++;
            }
        }
    }
    for (int i = 0; i < k - 1; i++) {
        for (int j = i + 1; j < k; j++) {
            if (edges[i][2] > edges[j][2]) {
                int temp = edges[i][0]; edges[i][0] = edges[j][0]; edges[j][0] = temp;
                temp = edges[i][1]; edges[i][1] = edges[j][1]; edges[j][1] = temp;
                temp = edges[i][2]; edges[i][2] = edges[j][2]; edges[j][2] = temp;
            }
        }
    }
    int parent[MAX_VEX];
    for (int i = 0; i < G.numVertexes; i++) parent[i] = -1;
    int find(int x) {
        while (parent[x] >= 0) x = parent[x];
        return x;
    }
    for (int i = 0; i < k; i++) {
        int p1 = find(edges[i][0]);
        int p2 = find(edges[i][1]);
        if (p1 != p2) {
            printf("Edge: %d - %d, Weight: %d\n", G.vexs[edges[i][0]], G.vexs[edges[i][1]], edges[i][2]);
            parent[p1] = p2;
        }
    }
}

void Dijkstra(MGraph G, int v) {
    int dist[MAX_VEX], path[MAX_VEX];
    int visited[MAX_VEX] = {0};
    for (int i = 0; i < G.numVertexes; i++) {
        dist[i] = G.arc[v][i] ? G.arc[v][i] : 9999;
        path[i] = G.arc[v][i] ? v : -1;
    }
    visited[v] = 1;
    dist[v] = 0;
    for (int i = 0; i < G.numVertexes - 1; i++) {
        int min = 9999, k = v;
        for (int j = 0; j < G.numVertexes; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                k = j;
            }
        }
        visited[k] = 1;
        for (int j = 0; j < G.numVertexes; j++) {
            if (!visited[j] && G.arc[k][j] && dist[k] + G.arc[k][j] < dist[j]) {
                dist[j] = dist[k] + G.arc[k][j];
                path[j] = k;
            }
        }
    }
    for (int i = 0; i < G.numVertexes; i++) {
        printf("%d -> %d: ", G.vexs[v], G.vexs[i]);
        if (dist[i] == 9999) printf("No path\n");
        else printf("Distance = %d\n", dist[i]);
    }
}

void Floyd(MGraph G) {
    int dist[MAX_VEX][MAX_VEX], path[MAX_VEX][MAX_VEX];
    for (int i = 0; i < G.numVertexes; i++) {
        for (int j = 0; j < G.numVertexes; j++) {
            if (G.arc[i][j]) {
                dist[i][j] = G.arc[i][j];
                path[i][j] = i;
            } else {
                dist[i][j] = 9999;
                path[i][j] = -1;
            }
        }
        dist[i][i] = 0;
    }
    for (int k = 0; k < G.numVertexes; k++) {
        for (int i = 0; i < G.numVertexes; i++) {
            for (int j = 0; j < G.numVertexes; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
    for (int i = 0; i < G.numVertexes; i++) {
        for (int j = 0; j < G.numVertexes; j++) {
            printf("%d -> %d: ", G.vexs[i], G.vexs[j]);
            if (dist[i][j] == 9999) printf("No path\n");
            else printf("Distance = %d\n", dist[i][j]);
        }
    }
}

void TopologicalSort(MGraph G) {
    int indegree[MAX_VEX] = {0};
    for (int i = 0; i < G.numVertexes; i++) {
        for (int j = 0; j < G.numVertexes; j++) {
            if (G.arc[i][j]) indegree[j]++;
        }
    }
    int stack[MAX_VEX], top = -1;
    for (int i = 0; i < G.numVertexes; i++) {
        if (indegree[i] == 0) stack[++top] = i;
    }
    printf("Topological Sort: ");
    while (top >= 0) {
        int v = stack[top--];
        printf("%d ", G.vexs[v]);
        for (int i = 0; i < G.numVertexes; i++) {
            if (G.arc[v][i]) {
                indegree[i]--;
                if (indegree[i] == 0) stack[++top] = i;
            }
        }
    }
    printf("\n");
}

void CriticalPath(MGraph G) {
    int ve[MAX_VEX], vl[MAX_VEX];
    int indegree[MAX_VEX] = {0};
    for (int i = 0; i < G.numVertexes; i++) {
        for (int j = 0; j < G.numVertexes; j++) {
            if (G.arc[i][j]) indegree[j]++;
        }
    }
    for (int i = 0; i < G.numVertexes; i++) ve[i] = 0;
    int stack[MAX_VEX], top = -1;
    for (int i = 0; i < G.numVertexes; i++) {
        if (indegree[i] == 0) stack[++top] = i;
    }
    int topo[MAX_VEX], count = 0;
    while (top >= 0) {
        int v = stack[top--];
        topo[count++] = v;
        for (int i = 0; i < G.numVertexes; i++) {
            if (G.arc[v][i]) {
                if (ve[v] + G.arc[v][i] > ve[i]) {
                    ve[i] = ve[v] + G.arc[v][i];
                }
                indegree[i]--;
                if (indegree[i] == 0) stack[++top] = i;
            }
        }
    }
    for (int i = 0; i < G.numVertexes; i++) vl[i] = ve[topo[count - 1]];
    for (int i = count - 2; i >= 0; i--) {
        for (int j = 0; j < G.numVertexes; j++) {
            if (G.arc[topo[i]][j]) {
                if (vl[j] - G.arc[topo[i]][j] < vl[topo[i]]) {
                    vl[topo[i]] = vl[j] - G.arc[topo[i]][j];
                }
            }
        }
    }
    printf("Critical Path:\n");
    for (int i = 0; i < G.numVertexes; i++) {
        for (int j = 0; j < G.numVertexes; j++) {
            if (G.arc[i][j]) {
                int ee = ve[i], el = vl[j] - G.arc[i][j];
                if (ee == el) printf("%d -> %d (Critical)\n", G.vexs[i], G.vexs[j]);
            }
        }
    }
}
