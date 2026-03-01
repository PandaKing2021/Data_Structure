/**
 * B+ Tree Header File
 *
 * B+ tree is a balanced search tree where all data is stored in leaf nodes.
 * Internal nodes only store routing keys. Leaf nodes are linked together,
 * enabling efficient range queries and sequential access.
 *
 * Key Features:
 * - All actual keys in leaf nodes only
 * - Leaf nodes form a sorted linked list
 * - All leaves at same depth
 * - Efficient for range scans and database indexing
 * - Commonly used in filesystems and databases
 */

#ifndef B_PLUS_TREE_H
#define B_PLUS_TREE_H

/**
 * ORDER: Maximum number of keys per node
 */
#define ORDER 3                   // B+ tree order (max keys per node)

/**
 * B+ Tree Node Structure
 */
typedef struct BPlusTreeNode {
    int numKeys;                   // Current number of keys in node
    int keys[ORDER];               // Array of keys stored in node
    struct BPlusTreeNode **children; // Child pointer array (ORDER+1 elements)
    struct BPlusTreeNode *next;    // Pointer to next leaf node (for leaf chain)
    int isLeaf;                   // Flag: 1 if leaf, 0 if internal node
} BPlusTreeNode, *BPlusTree;

/**
 * Create an empty B+ tree
 * @return Pointer to the root of the new B+ tree
 */
BPlusTree CreateBPlusTree(void);

/**
 * Search for a key in the B+ tree
 * @param T Pointer to B+ tree root
 * @param key Key to search for
 * @return 1 if found, 0 if not found
 */
int BPlusTreeSearch(BPlusTree *T, int key);

/**
 * Insert a key into the B+ tree
 * @param T Pointer to B+ tree root (may change)
 * @param key Key to insert
 */
void BPlusTreeInsert(BPlusTree *T, int key);

/**
 * Delete a key from the B+ tree
 * @param T Pointer to B+ tree root
 * @param key Key to delete
 */
void BPlusTreeDelete(BPlusTree *T, int key);

/**
 * Traverse B+ tree and print keys in sorted order
 * Uses the leaf chain for sequential access
 * @param T B+ tree root
 */
void TraverseBPlusTree(BPlusTree T);

/**
 * Print B+ tree structure showing all levels
 * @param T B+ tree root
 * @param level Current depth level
 */
void PrintBPlusTree(BPlusTree T, int level);

/**
 * Destroy B+ tree and free all memory
 * @param T B+ tree root
 */
void DestroyBPlusTree(BPlusTree T);

#endif
