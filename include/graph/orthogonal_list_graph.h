/**
 * Orthogonal List Graph (十字链表)
 *
 * An orthogonal list is a graph representation for directed graphs
 * that maintains separate link lists for in-degree and out-degree edges.
 * Each vertex has pointers to its first incoming and outgoing arcs.
 *
 * Key Features:
 * - Efficient for traversing both incoming and outgoing edges
 * - Useful for algorithms that need degree information
 * - Supports quick in-degree and out-degree queries
 * - More efficient than adjacency matrix for sparse graphs
 *
 * Time Complexity:
 * - Insert arc: O(1)
 * - Delete arc: O(degree of vertices)
 * - Find in-degree/out-degree: O(1)
 * - Find adjacent vertices: O(degree)
 */

#ifndef ORTHOGONAL_LIST_GRAPH_H
#define ORTHOGONAL_LIST_GRAPH_H

/**
 * Maximum number of vertices
 */
#define MAX_VEX 100

/**
 * Arc Box Node Structure
 * Represents a single directed arc (edge)
 */
typedef struct ArcBox {
    int tailvex, headvex;          // Positions of tail (source) and head (target) vertices
    int hlink, tlink;               // Pointers to next arcs with same head and tail
    int weight;                    // Arc weight
} ArcBox, *ArcBoxPtr;

/**
 * Vertex Node Structure
 * Represents a vertex with pointers to incoming and outgoing arcs
 */
typedef struct {
    int data;                       // Vertex data
    int firstin, firstout;          // Indices of first incoming and outgoing arcs
} VexNode;

/**
 * Orthogonal List Graph Structure
 */
typedef struct {
    VexNode xlist[MAX_VEX];         // Array of vertices
    int vexnum, arcnum;             // Number of vertices and arcs
    ArcBox *arcs;                   // Array of arcs
    int arcCapacity;                // Capacity of arcs array
} OLGraph;

/**
 * Initialize an empty orthogonal list graph
 * @param G Pointer to graph to initialize
 */
void InitOLGraph(OLGraph *G);

/**
 * Locate the position of a vertex in the graph
 * @param G Graph to search
 * @param v Vertex data to find
 * @return Position index of vertex, or -1 if not found
 */
int LocateVex(OLGraph G, int v);

/**
 * Insert a new vertex into the graph
 * @param G Pointer to graph
 * @param v Vertex data to insert
 * @return Position index of new vertex, or -1 if graph is full
 */
int InsertVex(OLGraph *G, int v);

/**
 * Insert a directed arc from v1 to v2
 * @param G Pointer to graph
 * @param v1 Tail (source) vertex
 * @param v2 Head (target) vertex
 * @param weight Arc weight
 * @return 1 on success, 0 on failure
 */
int InsertArc(OLGraph *G, int v1, int v2, int weight);

/**
 * Delete a directed arc from v1 to v2
 * @param G Pointer to graph
 * @param v1 Tail (source) vertex
 * @param v2 Head (target) vertex
 * @return 1 on success, 0 on failure
 */
int DeleteArc(OLGraph *G, int v1, int v2);

/**
 * Print the graph structure
 * @param G Graph to print
 */
void PrintOLGraph(OLGraph G);

/**
 * Destroy the graph and free all memory
 * @param G Pointer to graph to destroy
 */
void DestroyOLGraph(OLGraph *G);

/**
 * Get the in-degree of a vertex
 * @param G Graph
 * @param v Vertex position
 * @return Number of incoming arcs
 */
int GetInDegree(OLGraph G, int v);

/**
 * Get the out-degree of a vertex
 * @param G Graph
 * @param v Vertex position
 * @return Number of outgoing arcs
 */
int GetOutDegree(OLGraph G, int v);

#endif
