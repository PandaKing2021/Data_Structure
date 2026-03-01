#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define NULLKEY -1
#define DELKEY -2

typedef struct {
    int *elem;
    int count;
    int length;
} HashTable;

int Hash(int key);
void InitHashTable(HashTable *H, int size);
int SearchHash(HashTable H, int key);
int InsertHash(HashTable *H, int key);
int DeleteHash(HashTable *H, int key);
void PrintHashTable(HashTable H);

#endif
