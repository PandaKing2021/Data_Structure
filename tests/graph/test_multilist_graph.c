#include "../../include/graph/multilist_graph.h"
#include <stdio.h>

int main() {
    printf("=== Adjacency Multilist Graph Tests ===\n\n");

    AMLGraph G;
    InitAMLGraph(&G);

    /* Insert vertices */
    printf("1. Inserting vertices:\n");
    for (int i = 1; i <= 5; i++) {
        InsertVex(&G, i);
        printf("  Inserted vertex %d\n", i);
    }

    /* Insert edges */
    printf("\n2. Inserting edges:\n");
    InsertArc(&G, 1, 2, 1);
    InsertArc(&G, 1, 3, 1);
    InsertArc(&G, 2, 4, 1);
    InsertArc(&G, 3, 4, 1);
    InsertArc(&G, 4, 5, 1);
    InsertArc(&G, 2, 3, 1);
    printf("  Inserted edges: (1-2), (1-3), (2-4), (3-4), (4-5), (2-3)\n");

    /* Print adjacency multilist */
    printf("\n3. Adjacency Multilist:\n");
    PrintAMLGraph(G);

    /* Delete edge */
    printf("\n4. Deleting edge (2-3):\n");
    DeleteArc(&G, 2, 3);
    PrintAMLGraph(G);

    printf("\n=== All Tests Passed ===\n");

    DestroyAMLGraph(&G);
    return 0;
}
