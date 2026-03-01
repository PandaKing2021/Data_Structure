/**
 * Red-Black Tree Implementation
 *
 * A red-black tree is a self-balancing binary search tree that maintains
 * balance through node coloring and rotation operations. It guarantees
 * O(log n) time complexity for search, insert, and delete operations.
 *
 * Red-Black Tree Properties:
 * 1. Every node is either RED or BLACK
 * 2. The root is always BLACK
 * 3. Every leaf (NIL sentinel) is BLACK
 * 4. If a node is RED, both its children must be BLACK (no consecutive REDs)
 * 5. All paths from a node to its descendant NIL leaves contain the same
 *    number of BLACK nodes (black-height is uniform)
 *
 * The NIL sentinel node represents all null leaves and simplifies
 * boundary checking in the algorithms.
 */

#include "../../include/search/red_black_tree.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Global NIL sentinel node
 * All null pointers point to this node instead of NULL
 * This simplifies boundary checking and edge cases
 */
RBNode *NIL = NULL;

/**
 * Initialize the NIL sentinel node
 * Called once during program initialization
 * Creates a single black node that represents all leaf positions
 */
void InitRBTreeNil() {
    if (NIL == NULL) {
        NIL = (RBNode *)malloc(sizeof(RBNode));
        NIL->color = BLACK;                     // NIL is always black
        NIL->left = NIL->right = NIL->parent = NULL;  // NIL points to itself
    }
}

/**
 * Initialize an empty red-black tree
 * @param T Pointer to the tree root to initialize
 */
void InitRBTree(RBTree *T) {
    InitRBTreeNil();            // Ensure NIL is initialized
    *T = NIL;                   // Empty tree has NIL as root
}

/**
 * Create a new red-black tree node
 * New nodes are always inserted as RED
 *
 * @param key The key value for the new node
 * @return Pointer to the newly created node
 */
RBNode* CreateRBNode(int key) {
    RBNode *node = (RBNode *)malloc(sizeof(RBNode));
    node->key = key;
    node->color = RED;                     // New nodes are always red
    node->left = node->right = node->parent = NIL;
    return node;
}

/**
 * Perform left rotation on subtree rooted at node x
 * Reorganizes the tree to maintain balance during insert/delete
 *
 * Before:         After:
 *     x              y
 *    / \            / \
 *   a   y    =>    x   c
 *      / \        / \
 *     b   c      a   b
 *
 * @param T Pointer to tree root (may change if x is root)
 * @param x Node to rotate around
 */
void LeftRotate(RBTree *T, RBNode *x) {
    RBNode *y = x->right;          // y is x's right child
    x->right = y->left;            // Turn y's left subtree into x's right subtree

    if (y->left != NIL) {
        y->left->parent = x;       // Update y's left child's parent
    }

    y->parent = x->parent;         // Link x's parent to y

    if (x->parent == NIL) {
        *T = y;                     // x was root, now y is root
    } else if (x == x->parent->left) {
        x->parent->left = y;        // x was left child
    } else {
        x->parent->right = y;       // x was right child
    }

    y->left = x;                    // Put x on y's left
    x->parent = y;                  // Update x's parent
}

/**
 * Perform right rotation on subtree rooted at node y
 * Mirror image of left rotation
 *
 * Before:         After:
 *     y              x
 *    / \            / \
 *   x   c    =>    a   y
 *  / \                / \
 * a   b              b   c
 *
 * @param T Pointer to tree root (may change if y is root)
 * @param y Node to rotate around
 */
void RightRotate(RBTree *T, RBNode *y) {
    RBNode *x = y->left;           // x is y's left child
    y->left = x->right;            // Turn x's right subtree into y's left subtree

    if (x->right != NIL) {
        x->right->parent = y;      // Update x's right child's parent
    }

    x->parent = y->parent;         // Link y's parent to x

    if (y->parent == NIL) {
        *T = x;                     // y was root, now x is root
    } else if (y == y->parent->left) {
        y->parent->left = x;        // y was left child
    } else {
        y->parent->right = x;       // y was right child
    }

    x->right = y;                   // Put y on x's right
    y->parent = x;                  // Update y's parent
}

/**
 * Search for a key in the red-black tree
 * Standard BST search - O(log n)
 *
 * @param T Red-black tree root
 * @param key Key to search for
 * @return Pointer to node containing key, or NIL if not found
 */
RBNode* RBSearch(RBTree T, int key) {
    RBNode *node = T;

    while (node != NIL) {
        if (key < node->key) {
            node = node->left;      // Search left subtree
        } else if (key > node->key) {
            node = node->right;     // Search right subtree
        } else {
            return node;            // Key found
        }
    }

    return NIL;                     // Key not found
}

/**
 * Find the minimum node in a subtree
 * Traverse left until reaching a leaf
 *
 * @param node Root of subtree
 * @return Node with minimum key value
 */
RBNode* RBTreeMinimum(RBNode *node) {
    while (node->left != NIL) {
        node = node->left;
    }
    return node;
}

/**
 * Replace subtree u with subtree v
 * Used during deletion to move subtrees around
 * Does not update v's children, only v's parent and parent's child pointer
 *
 * @param T Pointer to tree root
 * @param u Subtree to be replaced
 * @param v Subtree to transplant in
 */
void RBTransplant(RBTree *T, RBNode *u, RBNode *v) {
    if (u->parent == NIL) {
        *T = v;                     // u was root
    } else if (u == u->parent->left) {
        u->parent->left = v;        // u was left child
    } else {
        u->parent->right = v;       // u was right child
    }

    v->parent = u->parent;          // Update v's parent
}

/**
 * Fix up the tree after insertion to restore red-black properties
 * Only called when the new node z is RED and its parent is also RED
 * (violates property 4: no consecutive RED nodes)
 *
 * @param T Pointer to tree root
 * @param z Newly inserted node that may violate properties
 */
void RBInsertFixup(RBTree *T, RBNode *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            // z's parent is left child of grandparent
            RBNode *y = z->parent->parent->right;  // Uncle node

            if (y->color == RED) {
                // Case 1: Uncle is RED
                // Solution: Recolor parent, uncle, and grandparent
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;              // Move up to grandparent
            } else {
                // Uncle is BLACK
                if (z == z->parent->right) {
                    // Case 2: z is right child (LR case)
                    // Solution: Left rotate parent, then handle as Case 3
                    z = z->parent;
                    LeftRotate(T, z);
                }

                // Case 3: z is left child (LL case)
                // Solution: Recolor and right rotate grandparent
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RightRotate(T, z->parent->parent);
            }
        } else {
            // Mirror case: z's parent is right child of grandparent
            RBNode *y = z->parent->parent->left;   // Uncle node

            if (y->color == RED) {
                // Case 1: Uncle is RED
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                // Uncle is BLACK
                if (z == z->parent->left) {
                    // Case 2: z is left child (RL case)
                    z = z->parent;
                    RightRotate(T, z);
                }

                // Case 3: z is right child (RR case)
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                LeftRotate(T, z->parent->parent);
            }
        }
    }

    // Ensure root is always black
    (*T)->color = BLACK;
}

/**
 * Insert a key into the red-black tree
 * First performs standard BST insertion, then calls fixup
 *
 * @param T Pointer to tree root (may change)
 * @param key Key to insert
 */
void RBInsert(RBTree *T, int key) {
    RBNode *z = CreateRBNode(key);
    RBNode *y = NIL;               // y will be z's parent
    RBNode *x = *T;

    // Standard BST insertion to find position
    while (x != NIL) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == NIL) {
        *T = z;                     // Tree was empty, z is new root
    } else if (z->key < y->key) {
        y->left = z;                // z is left child
    } else {
        y->right = z;               // z is right child
    }

    // Fix any red-black property violations
    RBInsertFixup(T, z);
}

/**
 * Fix up the tree after deletion to restore red-black properties
 * Called when node x is "doubly black" (has an extra black)
 *
 * @param T Pointer to tree root
 * @param x Node to start fixing from
 */
void RBDeleteFixup(RBTree *T, RBNode *x) {
    while (x != *T && x->color == BLACK) {
        if (x == x->parent->left) {
            // x is left child
            RBNode *w = x->parent->right;  // Sibling

            if (w->color == RED) {
                // Case 1: Sibling is RED
                // Solution: Recolor and left rotate, then handle as Case 2-4
                w->color = BLACK;
                x->parent->color = RED;
                LeftRotate(T, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == BLACK && w->right->color == BLACK) {
                // Case 2: Sibling's children are both BLACK
                // Solution: Recolor sibling and move up
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    // Case 3: Sibling's left is RED, right is BLACK
                    // Solution: Recolor and right rotate, then handle as Case 4
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(T, w);
                    w = x->parent->right;
                }

                // Case 4: Sibling's right is RED
                // Solution: Recolor and left rotate, terminate loop
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(T, x->parent);
                x = *T;
            }
        } else {
            // Mirror case: x is right child
            RBNode *w = x->parent->left;   // Sibling

            if (w->color == RED) {
                // Case 1: Sibling is RED
                w->color = BLACK;
                x->parent->color = RED;
                RightRotate(T, x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK) {
                // Case 2: Sibling's children are both BLACK
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    // Case 3: Sibling's right is RED, left is BLACK
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(T, w);
                    w = x->parent->left;
                }

                // Case 4: Sibling's left is RED
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(T, x->parent);
                x = *T;
            }
        }
    }

    x->color = BLACK;               // Ensure x is black
}

/**
 * Delete a key from the red-black tree
 * Performs BST deletion, then calls fixup if needed
 *
 * @param T Pointer to tree root
 * @param key Key to delete
 */
void RBDelete(RBTree *T, int key) {
    RBNode *z = RBSearch(*T, key);
    if (z == NIL) {
        return;                     // Key not found
    }

    RBNode *y = z;                  // y is node to be removed
    RBNode *x;
    RBColor yOriginalColor = y->color;

    // Case 1: z has no left child
    if (z->left == NIL) {
        x = z->right;
        RBTransplant(T, z, z->right);
    }
    // Case 2: z has no right child
    else if (z->right == NIL) {
        x = z->left;
        RBTransplant(T, z, z->left);
    }
    // Case 3: z has both children
    else {
        y = RBTreeMinimum(z->right);   // Find successor
        yOriginalColor = y->color;
        x = y->right;

        if (y->parent == z) {
            x->parent = y;
        } else {
            RBTransplant(T, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        RBTransplant(T, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;            // Copy z's color to y
    }

    // Fix up if we removed a black node
    if (yOriginalColor == BLACK) {
        RBDeleteFixup(T, x);
    }

    free(z);                         // Free the deleted node
}

/**
 * Perform inorder traversal and print nodes
 * Prints key with color indicator (R=RED, B=BLACK)
 *
 * @param T Red-black tree root
 */
void InorderRBTree(RBTree T) {
    if (T != NIL) {
        InorderRBTree(T->left);
        printf("%d(%s) ", T->key, T->color == RED ? "R" : "B");
        InorderRBTree(T->right);
    }
}
