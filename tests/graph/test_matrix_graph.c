#include <stdio.h>
#include "include/graph/matrix_graph.h"

int main() {
    printf("=== Matrix Graph Test ===\n");

    MGraph G;
    CreateMGraph(&G);

    printf("\n");
    PrintMGraph(G);

    printf("\nDFS starting from vertex 0:\n");
    int visited[MAX_VEX] = {0};
    DFS(G, 0, visited);
    printf("\n");

    printf("\nBFS starting from vertex 0:\n");
    for (int i = 0; i < G.numVertexes; i++) visited[i] = 0;
    BFS(G, 0, visited);
    printf("\n");

    printf("\n=== Prim's MST ===\n");
    Prim(G);

    printf("\n=== Kruskal's MST ===\n");
    Kruskal(G);

    printf("\n=== Dijkstra's Shortest Path ===\n");
    Dijkstra(G, 0);

    printf("\n=== Floyd's All-Pairs Shortest Path ===\n");
    Floyd(G);

    printf("\n=== Topological Sort ===\n");
    TopologicalSort(G);

    printf("\n=== Critical Path ===\n");
    CriticalPath(G);

    return 0;
}
