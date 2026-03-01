#include "../../include/graph/orthogonal_list_graph.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Initialize the Orthogonal List Graph structure.
 * Sets up the graph with zero vertices and edges.
 */
void InitOLGraph(OLGraph *G) {
    G->vexnum = 0;
    G->arcnum = 0;
    G->arcCapacity = 100;
    G->arcs = (ArcBox *)malloc(G->arcCapacity * sizeof(ArcBox));

    for (int i = 0; i < MAX_VEX; i++) {
        G->xlist[i].data = 0;
        G->xlist[i].firstin = -1;
        G->xlist[i].firstout = -1;
    }
}

/**
 * Locate the position of a vertex in the graph.
 * @param G The graph structure
 * @param v The vertex value to search for
 * @return The index of the vertex, or -1 if not found
 */
int LocateVex(OLGraph G, int v) {
    for (int i = 0; i < G.vexnum; i++) {
        if (G.xlist[i].data == v) {
            return i;
        }
    }
    return -1;
}

/**
 * Insert a new vertex into the graph.
 * @param G The graph structure
 * @param v The vertex value to insert
 * @return 1 on success, 0 on failure (vertex exists or graph is full)
 */
int InsertVex(OLGraph *G, int v) {
    if (G->vexnum >= MAX_VEX) {
        return 0;
    }

    if (LocateVex(*G, v) != -1) {
        return 0;
    }

    G->xlist[G->vexnum].data = v;
    G->xlist[G->vexnum].firstin = -1;
    G->xlist[G->vexnum].firstout = -1;
    G->vexnum++;

    return 1;
}

/**
 * Insert a directed arc from v1 to v2.
 * @param G The graph structure
 * @param v1 The tail vertex
 * @param v2 The head vertex
 * @param weight The weight of the arc
 * @return 1 on success, 0 on failure
 */
int InsertArc(OLGraph *G, int v1, int v2, int weight) {
    int tail = LocateVex(*G, v1);
    int head = LocateVex(*G, v2);

    if (tail == -1 || head == -1) {
        return 0;
    }

    for (int i = 0; i < G->arcnum; i++) {
        if (G->arcs[i].tailvex == tail && G->arcs[i].headvex == head) {
            return 0;
        }
    }

    if (G->arcnum >= G->arcCapacity) {
        G->arcCapacity *= 2;
        G->arcs = (ArcBox *)realloc(G->arcs, G->arcCapacity * sizeof(ArcBox));
    }

    int arcIndex = G->arcnum;
    G->arcs[arcIndex].tailvex = tail;
    G->arcs[arcIndex].headvex = head;
    G->arcs[arcIndex].weight = weight;
    G->arcs[arcIndex].hlink = G->xlist[head].firstin;
    G->arcs[arcIndex].tlink = G->xlist[tail].firstout;

    G->xlist[head].firstin = arcIndex;
    G->xlist[tail].firstout = arcIndex;

    G->arcnum++;

    return 1;
}

/**
 * Delete a directed arc from v1 to v2.
 * @param G The graph structure
 * @param v1 The tail vertex
 * @param v2 The head vertex
 * @return 1 on success, 0 on failure
 */
int DeleteArc(OLGraph *G, int v1, int v2) {
    int tail = LocateVex(*G, v1);
    int head = LocateVex(*G, v2);

    if (tail == -1 || head == -1) {
        return 0;
    }

    int arcIndex = -1;
    for (int i = 0; i < G->arcnum; i++) {
        if (G->arcs[i].tailvex == tail && G->arcs[i].headvex == head) {
            arcIndex = i;
            break;
        }
    }

    if (arcIndex == -1) {
        return 0;
    }

    if (G->xlist[tail].firstout == arcIndex) {
        G->xlist[tail].firstout = G->arcs[arcIndex].tlink;
    } else {
        int prev = G->xlist[tail].firstout;
        while (prev != -1 && G->arcs[prev].tlink != arcIndex) {
            prev = G->arcs[prev].tlink;
        }
        if (prev != -1) {
            G->arcs[prev].tlink = G->arcs[arcIndex].tlink;
        }
    }

    if (G->xlist[head].firstin == arcIndex) {
        G->xlist[head].firstin = G->arcs[arcIndex].hlink;
    } else {
        int prev = G->xlist[head].firstin;
        while (prev != -1 && G->arcs[prev].hlink != arcIndex) {
            prev = G->arcs[prev].hlink;
        }
        if (prev != -1) {
            G->arcs[prev].hlink = G->arcs[arcIndex].hlink;
        }
    }

    for (int i = arcIndex; i < G->arcnum - 1; i++) {
        G->arcs[i] = G->arcs[i + 1];

        for (int j = 0; j < G->vexnum; j++) {
            if (G->xlist[j].firstin == i + 1) {
                G->xlist[j].firstin = i;
            }
            if (G->xlist[j].firstout == i + 1) {
                G->xlist[j].firstout = i;
            }
        }
    }

    G->arcnum--;
    return 1;
}

/**
 * Get the in-degree of a vertex (number of incoming arcs).
 * @param G The graph structure
 * @param v The vertex value
 * @return The in-degree, or -1 if vertex not found
 */
int GetInDegree(OLGraph G, int v) {
    int pos = LocateVex(G, v);
    if (pos == -1) {
        return -1;
    }

    int count = 0;
    int arc = G.xlist[pos].firstin;

    while (arc != -1) {
        count++;
        arc = G.arcs[arc].hlink;
    }

    return count;
}

/**
 * Get the out-degree of a vertex (number of outgoing arcs).
 * @param G The graph structure
 * @param v The vertex value
 * @return The out-degree, or -1 if vertex not found
 */
int GetOutDegree(OLGraph G, int v) {
    int pos = LocateVex(G, v);
    if (pos == -1) {
        return -1;
    }

    int count = 0;
    int arc = G.xlist[pos].firstout;

    while (arc != -1) {
        count++;
        arc = G.arcs[arc].tlink;
    }

    return count;
}

/**
 * Print the Orthogonal List Graph structure.
 * Displays all vertices with their in/out arcs and weights.
 * @param G The graph structure to print
 */
void PrintOLGraph(OLGraph G) {
    printf("OLGraph (Vertices: %d, Arcs: %d)\n", G.vexnum, G.arcnum);

    for (int i = 0; i < G.vexnum; i++) {
        printf("V%d(%d): [In=%d, Out=%d]\n", i, G.xlist[i].data,
               GetInDegree(G, G.xlist[i].data),
               GetOutDegree(G, G.xlist[i].data));

        printf("  Out arcs: ");
        int arc = G.xlist[i].firstout;
        while (arc != -1) {
            printf("-> V%d(%d)[w=%d] ",
                   G.arcs[arc].headvex,
                   G.xlist[G.arcs[arc].headvex].data,
                   G.arcs[arc].weight);
            arc = G.arcs[arc].tlink;
        }
        printf("\n");

        printf("  In arcs: ");
        arc = G.xlist[i].firstin;
        while (arc != -1) {
            printf("<- V%d(%d)[w=%d] ",
                   G.arcs[arc].tailvex,
                   G.xlist[G.arcs[arc].tailvex].data,
                   G.arcs[arc].weight);
            arc = G.arcs[arc].hlink;
        }
        printf("\n");
    }
}

/**
 * Destroy the Orthogonal List Graph and free all allocated memory.
 * @param G The graph structure to destroy
 */
void DestroyOLGraph(OLGraph *G) {
    if (G->arcs) {
        free(G->arcs);
        G->arcs = NULL;
    }
    G->vexnum = 0;
    G->arcnum = 0;
    G->arcCapacity = 0;

    for (int i = 0; i < MAX_VEX; i++) {
        G->xlist[i].data = 0;
        G->xlist[i].firstin = -1;
        G->xlist[i].firstout = -1;
    }
}
