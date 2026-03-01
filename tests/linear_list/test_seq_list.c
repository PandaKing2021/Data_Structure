#include <stdio.h>
#include "include/linear_list/seq_list.h"

int main() {
    printf("=== Sequential List Test ===\n");

    SeqList L;
    InitList(&L);

    printf("Insert 10, 20, 30, 40, 50\n");
    ListInsert(&L, 1, 10);
    ListInsert(&L, 2, 20);
    ListInsert(&L, 3, 30);
    ListInsert(&L, 4, 40);
    ListInsert(&L, 5, 50);
    PrintList(L);

    printf("Length: %d\n", ListLength(L));
    printf("Empty: %d\n", ListEmpty(L));

    int e;
    GetElem(L, 3, &e);
    printf("Element at position 3: %d\n", e);

    printf("Locate 30: position %d\n", LocateElem(L, 30));

    printf("Delete element at position 2\n");
    ListDelete(&L, 2, &e);
    PrintList(L);
    printf("Deleted element: %d\n", e);

    return 0;
}
