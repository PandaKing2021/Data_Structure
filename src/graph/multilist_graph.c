/**
 * Adjacency Multilist Graph Implementation (邻接多重表)
 *
 * Implementation of adjacency multilist representation for undirected graphs.
 * Each edge is stored once, unlike adjacency lists where edges appear twice.
 */

#include "../../include/graph/multilist_graph.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Initialize an empty adjacency multilist graph
 */
void InitAMLGraph(AMLGraph *G) {
    G->vexnum = 0;
    G->edgenum = 0;
    for (int i = 0; i < MAX_VEX; i++) {
        G->adjmulist[i].data = 0;
        G->adjmulist[i].firstedge = NULL;
    }
}

/**
 * Locate vertex by data value
 * Returns the index of the vertex with given data
 */
int LocateVex(AMLGraph G, int v) {
    for (int i = 0; i < G.vexnum; i++) {
        if (G.adjmulist[i].data == v) {
            return i;
        }
    }
    return -1;
}

/**
 * Insert a new vertex into the graph
 * Returns the index of the newly inserted vertex
 */
int InsertVex(AMLGraph *G, int v) {
    if (G->vexnum >= MAX_VEX) return -1;

    G->adjmulist[G->vexnum].data = v;
    G->adjmulist[G->vexnum].firstedge = NULL;
    return G->vexnum++;
}

/**
 * Insert an edge between two vertices
 * Creates a single edge node that is linked from both vertices
 */
int InsertArc(AMLGraph *G, int v1, int v2, int weight) {
    int i = LocateVex(*G, v1);
    int j = LocateVex(*G, v2);

    if (i == -1 || j == -1) return 0;

    // Create new edge node
    EBoxPtr p = (EBoxPtr)malloc(sizeof(EBox));
    if (p == NULL) return 0;

    p->mark = 0;
    p->ivex = i;
    p->jvex = j;
    p->weight = weight;

    // Link the edge from both vertices
    p->ilink = G->adjmulist[i].firstedge;
    G->adjmulist[i].firstedge = p;

    p->jlink = G->adjmulist[j].firstedge;
    G->adjmulist[j].firstedge = p;

    G->edgenum++;
    return 1;
}

/**
 * Delete an edge between two vertices
 * Removes the edge and updates both vertices' edge lists
 */
int DeleteArc(AMLGraph *G, int v1, int v2) {
    int i = LocateVex(*G, v1);
    int j = LocateVex(*G, v2);

    if (i == -1 || j == -1) return 0;

    EBoxPtr p = G->adjmulist[i].firstedge;
    EBoxPtr prev = NULL;

    // Search and remove from vertex i's edge list
    while (p != NULL) {
        if ((p->ivex == i && p->jvex == j) || (p->ivex == j && p->jvex == i)) {
            if (prev == NULL) {
                G->adjmulist[i].firstedge = p->ilink;
            } else {
                prev->ilink = p->ilink;
            }
            break;
        }
        prev = p;
        p = p->ilink;
    }

    if (p == NULL) return 0;

    // Remove from vertex j's edge list
    EBoxPtr q = G->adjmulist[j].firstedge;
    prev = NULL;
    while (q != NULL) {
        if (q == p) {
            if (prev == NULL) {
                G->adjmulist[j].firstedge = q->jlink;
            } else {
                prev->jlink = q->jlink;
            }
            break;
        }
        prev = q;
        q = q->jlink;
    }

    free(p);
    G->edgenum--;
    return 1;
}

/**
 * Print the graph structure showing vertices and edges
 */
void PrintAMLGraph(AMLGraph G) {
    printf("Adjacency Multilist Graph:\n");
    printf("Vertices: %d, Edges: %d\n", G.vexnum, G.edgenum);

    for (int i = 0; i < G.vexnum; i++) {
        printf("Vertex %d: ", G.adjmulist[i].data);
        EBoxPtr p = G.adjmulist[i].firstedge;
        while (p != NULL) {
            int other = (p->ivex == i) ? p->jvex : p->ivex;
            printf("%d(%d) ", G.adjmulist[other].data, p->weight);
            p = (p->ivex == i) ? p->ilink : p->jlink;
        }
        printf("\n");
    }
}

/**
 * Destroy the graph and free all allocated memory
 */
void DestroyAMLGraph(AMLGraph *G) {
    for (int i = 0; i < G->vexnum; i++) {
        EBoxPtr p = G->adjmulist[i].firstedge;
        while (p != NULL) {
            EBoxPtr temp = p;
            if (p->ivex == i) {
                p = p->ilink;
            } else {
                p = p->jlink;
            }
            free(temp);
        }
    }
    G->vexnum = 0;
    G->edgenum = 0;
}
