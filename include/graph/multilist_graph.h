/**
 * Adjacency Multilist Graph (邻接多重表)
 *
 * An adjacency multilist is a graph representation for undirected graphs
 * that stores each edge only once, unlike adjacency list where edges
 * appear twice. It is efficient for edge deletion operations.
 *
 * Key Features:
 * - Each edge is represented by a single node
 * - Each vertex points to edges incident to it
 * - Efficient for edge deletion operations
 * - More compact than adjacency list for sparse graphs
 *
 * Time Complexity:
 * - Insert edge: O(1)
 * - Delete edge: O(1) with vertex pointers
 * - Find adjacent vertices: O(degree of vertex)
 */

#ifndef MULTILIST_GRAPH_H
#define MULTILIST_GRAPH_H

/**
 * Maximum number of vertices
 */
#define MAX_VEX 100

/**
 * Edge Box Node Structure
 * Represents a single edge in an undirected graph using multilist
 */
typedef struct EBox {
    int mark;                        // Visit flag: 0=unvisited, 1=visited
    int ivex, jvex;                 // Positions of two vertices connected by this edge
    struct EBox *ilink, *jlink;      // Pointers to next edges incident to ivex and jvex
    int weight;                     // Edge weight
} EBox, *EBoxPtr;

/**
 * Vertex Box Structure
 * Represents a vertex and its incident edges
 */
typedef struct {
    int data;                       // Vertex data
    EBoxPtr firstedge;              // Pointer to first edge incident to this vertex
} VexBox;

/**
 * Adjacency Multilist Graph Structure
 */
typedef struct {
    VexBox adjmulist[MAX_VEX];      // Array of vertices
    int vexnum, edgenum;            // Number of vertices and edges
} AMLGraph;

/**
 * Initialize an empty adjacency multilist graph
 * @param G Pointer to graph to initialize
 */
void InitAMLGraph(AMLGraph *G);

/**
 * Locate the position of a vertex in the graph
 * @param G Graph to search
 * @param v Vertex data to find
 * @return Position index of vertex, or -1 if not found
 */
int LocateVex(AMLGraph G, int v);

/**
 * Insert a new vertex into the graph
 * @param G Pointer to graph
 * @param v Vertex data to insert
 * @return Position index of new vertex, or -1 if graph is full
 */
int InsertVex(AMLGraph *G, int v);

/**
 * Insert an edge between two vertices
 * @param G Pointer to graph
 * @param v1 First vertex
 * @param v2 Second vertex
 * @param weight Edge weight
 * @return 1 on success, 0 on failure
 */
int InsertArc(AMLGraph *G, int v1, int v2, int weight);

/**
 * Delete an edge between two vertices
 * @param G Pointer to graph
 * @param v1 First vertex
 * @param v2 Second vertex
 * @return 1 on success, 0 on failure
 */
int DeleteArc(AMLGraph *G, int v1, int v2);

/**
 * Print the graph structure
 * @param G Graph to print
 */
void PrintAMLGraph(AMLGraph G);

/**
 * Destroy the graph and free all memory
 * @param G Pointer to graph to destroy
 */
void DestroyAMLGraph(AMLGraph *G);

#endif
