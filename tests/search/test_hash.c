#include <stdio.h>
#include <stdlib.h>
#include "include/search/hash_table.h"

int main() {
    printf("=== Hash Table Test ===\n");

    HashTable H;
    InitHashTable(&H, 13);

    printf("Insert keys: 19, 14, 23, 1, 68, 20, 84, 27, 55, 11\n");
    InsertHash(&H, 19);
    InsertHash(&H, 14);
    InsertHash(&H, 23);
    InsertHash(&H, 1);
    InsertHash(&H, 68);
    InsertHash(&H, 20);
    InsertHash(&H, 84);
    InsertHash(&H, 27);
    InsertHash(&H, 55);
    InsertHash(&H, 11);

    PrintHashTable(H);

    printf("\nSearch 23: %s\n", SearchHash(H, 23) != -1 ? "Found" : "Not found");
    printf("Search 99: %s\n", SearchHash(H, 99) != -1 ? "Found" : "Not found");

    printf("\nDelete 14\n");
    DeleteHash(&H, 14);
    PrintHashTable(H);

    free(H.elem);

    return 0;
}
