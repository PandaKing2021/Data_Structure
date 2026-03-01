#include <stdio.h>
#include <stdlib.h>
#include "include/search/hash_table.h"

int Hash(int key) {
    return key % 13;
}

void InitHashTable(HashTable *H, int size) {
    H->count = 0;
    H->length = size;
    H->elem = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        H->elem[i] = NULLKEY;
    }
}

int SearchHash(HashTable H, int key) {
    int addr = Hash(key);
    while (H.elem[addr] != key && H.elem[addr] != NULLKEY) {
        addr = (addr + 1) % H.length;
    }
    if (H.elem[addr] == key) {
        return addr;
    } else {
        return -1;
    }
}

int InsertHash(HashTable *H, int key) {
    int addr = Hash(key);
    while (H->elem[addr] != NULLKEY && H->elem[addr] != DELKEY) {
        addr = (addr + 1) % H->length;
    }
    if (H->elem[addr] == DELKEY || H->elem[addr] == NULLKEY) {
        H->elem[addr] = key;
        H->count++;
        return 1;
    }
    return 0;
}

int DeleteHash(HashTable *H, int key) {
    int addr = SearchHash(*H, key);
    if (addr != -1) {
        H->elem[addr] = DELKEY;
        H->count--;
        return 1;
    }
    return 0;
}

void PrintHashTable(HashTable H) {
    printf("Hash Table:\n");
    for (int i = 0; i < H.length; i++) {
        if (H.elem[i] != NULLKEY && H.elem[i] != DELKEY) {
            printf("[%d] = %d\n", i, H.elem[i]);
        }
    }
}
