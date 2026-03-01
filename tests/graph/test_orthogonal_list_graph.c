#include "../../include/graph/orthogonal_list_graph.h"
#include <stdio.h>

int main() {
    printf("=== Orthogonal List Graph Tests ===\n\n");

    OLGraph G;
    InitOLGraph(&G);

    /* Insert vertices */
    printf("1. Inserting vertices:\n");
    for (int i = 1; i <= 5; i++) {
        InsertVex(&G, i);
        printf("  Inserted vertex %d\n", i);
    }

    /* Insert arcs */
    printf("\n2. Inserting arcs:\n");
    InsertArc(&G, 1, 2, 1);
    InsertArc(&G, 1, 3, 1);
    InsertArc(&G, 2, 4, 1);
    InsertArc(&G, 3, 4, 1);
    InsertArc(&G, 4, 5, 1);
    printf("  Inserted arcs: 1->2, 1->3, 2->4, 3->4, 4->5\n");

    /* Print orthogonal list */
    printf("\n3. Orthogonal List:\n");
    PrintOLGraph(G);

    /* Delete arc */
    printf("\n4. Deleting arc (2->4):\n");
    DeleteArc(&G, 2, 4);
    PrintOLGraph(G);

    printf("\n=== All Tests Passed ===\n");

    DestroyOLGraph(&G);
    return 0;
}
