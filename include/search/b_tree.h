/**
 * B-Tree Header File
 *
 * B-tree is a balanced search tree optimized for disk storage systems.
 * It maintains sorted data and allows efficient search, insertion, and
 * deletion operations in O(log n) time.
 *
 * Key Features:
 * - All leaves at same depth
 * - Node degree: at least ceil(M/2) and at most M children
 * - Keys: at least ceil(M/2)-1 and at most M-1 per node
 * - Ideal for database indexing and file systems
 */

#ifndef B_TREE_H
#define B_TREE_H

/**
 * M: Order of the B-tree (maximum number of children)
 * MIN_DEGREE: Minimum degree (half of order)
 * MAX_KEYS: Maximum keys per node (order - 1)
 */
#define M 3                     // B-tree order
#define MIN_DEGREE ((M + 1) / 2)
#define MAX_KEYS (M - 1)

/**
 * B-tree Node Structure
 */
typedef struct BTreeNode {
    int n;                            // Current number of keys in node
    int keys[MAX_KEYS];               // Array of keys stored in node
    struct BTreeNode *children[MAX_KEYS + 1]; // Child pointers (n+1 for n keys)
    int isLeaf;                       // Flag: 1 if leaf node, 0 if internal
} BTreeNode, *BTree;

/**
 * Create an empty B-tree
 * @return Pointer to the root of the new B-tree
 */
BTree CreateBTree(void);

/**
 * Search for a key in the B-tree
 * @param node Current node to search
 * @param key Key to search for
 * @param idx Output parameter: index where key was found or should be
 * @return Pointer to node containing key, or NULL if not found
 */
BTreeNode* BTreeSearch(BTreeNode *node, int key, int *idx);

/**
 * Insert a key into the B-tree
 * @param T Pointer to B-tree root (may change if root splits)
 * @param key Key to insert
 */
void BTreeInsert(BTree *T, int key);

/**
 * Delete a key from the B-tree
 * @param T Pointer to B-tree root
 * @param key Key to delete
 */
void BTreeDelete(BTree *T, int key);

/**
 * Split a full child node during insertion
 * @param parent Parent node containing the full child
 * @param i Index of the child to split
 */
void SplitChild(BTreeNode *parent, int i);

/**
 * Insert key into a node that is not full
 * @param node Node to insert into (must have space)
 * @param key Key to insert
 */
void InsertNonFull(BTreeNode *node, int key);

/**
 * Find minimum key in subtree
 * @param node Root of subtree
 * @return Minimum key value
 */
int FindMin(BTreeNode *node);

/**
 * Remove key from leaf node
 * @param node Leaf node
 * @param idx Index of key to remove
 */
void RemoveFromLeaf(BTreeNode *node, int idx);

/**
 * Remove key from internal node
 * @param node Internal node
 * @param idx Index of key to remove
 */
void RemoveFromInternal(BTreeNode *node, int idx);

/**
 * Borrow key from left sibling
 * @param curr Current node needing key
 * @param left Left sibling node
 * @param idx Index position
 */
void BorrowFromLeft(BTreeNode *curr, BTreeNode *left, int idx);

/**
 * Borrow key from right sibling
 * @param curr Current node needing key
 * @param right Right sibling node
 * @param idx Index position
 */
void BorrowFromRight(BTreeNode *curr, BTreeNode *right, int idx);

/**
 * Merge node with left sibling
 * @param curr Current node
 * @param left Left sibling to merge
 * @param idx Index position
 */
void Merge(BTreeNode *curr, BTreeNode *left, int idx);

/**
 * Traverse and print B-tree structure
 * @param node Current node
 * @param level Current depth level
 */
void TraverseBTree(BTreeNode *node, int level);

#endif
