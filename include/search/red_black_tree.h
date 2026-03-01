/**
 * Red-Black Tree Header File
 *
 * A red-black tree is a self-balancing binary search tree that ensures
 * the tree remains approximately balanced during insertions and deletions.
 * It maintains balance through coloring rules and rotation operations.
 *
 * Properties:
 * 1. Every node is either red or black
 * 2. Root is always black
 * 3. Every leaf (NIL) is black
 * 4. If a node is red, both its children are black (no consecutive reds)
 * 5. All paths from a node to its descendant leaves contain same number of black nodes
 *
 * This guarantees O(log n) time for search, insert, and delete operations.
 */

#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

/**
 * Color enumeration for red-black tree nodes
 */
typedef enum { RED, BLACK } RBColor;

/**
 * Red-Black Tree Node Structure
 */
typedef struct RBNode {
    int key;                        // The key value stored in this node
    RBColor color;                  // Node color: RED or BLACK
    struct RBNode *left, *right;    // Left and right child pointers
    struct RBNode *parent;          // Parent pointer (used for rotations)
} RBNode, *RBTree;

/**
 * NIL sentinel node (represents all null leaves)
 * All leaf pointers point to this NIL node
 */
extern RBNode *NIL;

/**
 * Initialize the NIL sentinel node
 * Called once at program startup
 */
void InitRBTreeNil();

/**
 * Initialize an empty red-black tree
 * @param T Pointer to the tree root to initialize
 */
void InitRBTree(RBTree *T);

/**
 * Search for a key in the red-black tree
 * @param T Red-black tree root
 * @param key Key to search for
 * @return Pointer to node containing key, or NIL if not found
 */
RBNode* RBSearch(RBTree T, int key);

/**
 * Insert a key into the red-black tree
 * @param T Pointer to tree root (may change)
 * @param key Key to insert
 */
void RBInsert(RBTree *T, int key);

/**
 * Delete a key from the red-black tree
 * @param T Pointer to tree root (may change)
 * @param key Key to delete
 */
void RBDelete(RBTree *T, int key);

/**
 * Perform left rotation on a subtree
 * @param T Pointer to tree root
 * @param x Node to rotate around
 */
void LeftRotate(RBTree *T, RBNode *x);

/**
 * Perform right rotation on a subtree
 * @param T Pointer to tree root
 * @param y Node to rotate around
 */
void RightRotate(RBTree *T, RBNode *y);

/**
 * Fix up the tree after insertion to maintain red-black properties
 * @param T Pointer to tree root
 * @param z Newly inserted node
 */
void RBInsertFixup(RBTree *T, RBNode *z);

/**
 * Fix up the tree after deletion to maintain red-black properties
 * @param T Pointer to tree root
 * @param x Node where fixup should start
 */
void RBDeleteFixup(RBTree *T, RBNode *x);

/**
 * Find the node with minimum key in a subtree
 * @param node Root of subtree
 * @return Pointer to node with minimum key
 */
RBNode* RBTreeMinimum(RBNode *node);

/**
 * Perform inorder traversal and print keys
 * @param T Red-black tree root
 */
void InorderRBTree(RBTree T);

/**
 * Helper function: create a new red-black tree node
 * @param key Key value for the new node
 * @return Pointer to newly created node
 */
RBNode* CreateRBNode(int key);

/**
 * Helper function: transplant subtree u with subtree v
 * Used during deletion to replace one subtree with another
 * @param T Pointer to tree root
 * @param u Subtree to be replaced
 * @param v Subtree to transplant in
 */
void RBTransplant(RBTree *T, RBNode *u, RBNode *v);

#endif
