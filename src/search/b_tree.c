/**
 * B-Tree Implementation
 *
 * A B-tree is a self-balancing search tree that maintains sorted data
 * and allows searches, sequential access, insertions, and deletions in
 * logarithmic time. It is commonly used in databases and file systems.
 *
 * Properties:
 * - All leaf nodes are at the same level
 * - Every node (except root) must have at least MIN_DEGREE-1 keys
 * - Every node can have at most M-1 keys (where M is the order)
 * - A node with n keys has n+1 children
 * - Keys are stored in sorted order within each node
 */

#include "../../include/search/b_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Create a new B-tree node
 * @param isLeaf Flag indicating whether the node is a leaf
 * @return Pointer to the newly created node
 */
BTreeNode* CreateBTreeNode(int isLeaf) {
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->n = 0;                   // Initialize with zero keys
    node->isLeaf = isLeaf;         // Set leaf flag

    // Initialize all keys and child pointers to zero/NULL
    for (int i = 0; i <= MAX_KEYS; i++) {
        node->keys[i] = 0;
        node->children[i] = NULL;
    }

    return node;
}

/**
 * Create an empty B-tree
 * @return Pointer to the root of the new B-tree
 */
BTree CreateBTree(void) {
    BTree T = CreateBTreeNode(1);  // Create a leaf node as root
    return T;
}

/**
 * Search for a key in the B-tree
 * @param node Current node being searched
 * @param key Key to search for
 * @param idx Output parameter for the index where key was found or should be
 * @return Pointer to node containing the key, or NULL if not found
 */
BTreeNode* BTreeSearch(BTreeNode *node, int key, int *idx) {
    if (node == NULL) return NULL;

    int i = 0;
    // Find the first key greater than or equal to the search key
    while (i < node->n && key > node->keys[i]) {
        i++;
    }

    *idx = i;

    // Key found at this node
    if (i < node->n && key == node->keys[i]) {
        return node;
    }

    // Key not found and we've reached a leaf
    if (node->isLeaf) {
        return NULL;
    }

    // Recursively search the appropriate child
    return BTreeSearch(node->children[i], key, idx);
}

/**
 * Split a full child node during insertion
 * @param parent Parent node containing the child to split
 * @param i Index of the child to split
 */
void SplitChild(BTreeNode *parent, int i) {
    BTreeNode *full = parent->children[i];  // The full child node
    BTreeNode *newNode = CreateBTreeNode(full->isLeaf);

    int mid = MAX_KEYS / 2;

    // Copy the second half of keys to the new node
    for (int j = mid + 1; j < MAX_KEYS; j++) {
        newNode->keys[j - (mid + 1)] = full->keys[j];
    }

    // If not a leaf node, copy the child pointers as well
    if (!full->isLeaf) {
        for (int j = mid + 1; j <= MAX_KEYS; j++) {
            newNode->children[j - (mid + 1)] = full->children[j];
        }
    }

    newNode->n = MAX_KEYS - mid - 1;  // New node's key count
    full->n = mid;                     // Original node's new key count

    // Make room in parent for the new child
    for (int j = parent->n; j > i; j--) {
        parent->keys[j] = parent->keys[j - 1];
        parent->children[j + 1] = parent->children[j];
    }

    // Insert the median key into parent
    parent->keys[i] = full->keys[mid];
    parent->children[i + 1] = newNode;
    parent->n++;
}

/**
 * Insert a key into a node that is not full
 * @param node Node to insert into (guaranteed not full)
 * @param key Key to insert
 */
void InsertNonFull(BTreeNode *node, int key) {
    int i = node->n - 1;

    if (node->isLeaf) {
        // Leaf node: insert directly maintaining sorted order
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->n++;
    } else {
        // Internal node: find appropriate child
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;

        // If child is full, split it first
        if (node->children[i]->n == MAX_KEYS) {
            SplitChild(node, i);
            if (key > node->keys[i]) {
                i++;
            }
        }
        InsertNonFull(node->children[i], key);
    }
}

/**
 * Insert a key into the B-tree
 * @param T Pointer to the B-tree root (may change)
 * @param key Key to insert
 */
void BTreeInsert(BTree *T, int key) {
    if (*T == NULL) {
        *T = CreateBTree();
        (*T)->keys[0] = key;
        (*T)->n = 1;
        return;
    }

    BTreeNode *root = *T;

    // If root is full, tree grows in height
    if (root->n == MAX_KEYS) {
        BTreeNode *newRoot = CreateBTreeNode(0);
        newRoot->children[0] = root;
        *T = newRoot;
        SplitChild(newRoot, 0);
        InsertNonFull(newRoot, key);
    } else {
        InsertNonFull(root, key);
    }
}

/**
 * Find the minimum key in a subtree
 * @param node Root of the subtree
 * @return Minimum key value
 */
int FindMin(BTreeNode *node) {
    // Traverse to the leftmost leaf
    while (!node->isLeaf) {
        node = node->children[0];
    }
    return node->keys[0];
}

/**
 * Remove a key from a leaf node
 * @param node Leaf node to remove from
 * @param idx Index of key to remove
 */
void RemoveFromLeaf(BTreeNode *node, int idx) {
    // Shift all keys after the removed key one position left
    for (int i = idx + 1; i < node->n; i++) {
        node->keys[i - 1] = node->keys[i];
    }
    node->n--;
}

/**
 * Remove a key from an internal node
 * @param node Internal node to remove from
 * @param idx Index of key to remove
 */
void RemoveFromInternal(BTreeNode *node, int idx) {
    // Replace with minimum from right subtree
    node->keys[idx] = FindMin(node->children[idx + 1]);

    // Shift remaining keys
    for (int i = idx + 1; i < node->n; i++) {
        node->keys[i] = node->keys[i + 1];
    }
}

/**
 * Borrow a key from left sibling
 * @param curr Current node needing a key
 * @param left Left sibling node
 * @param idx Index position to insert
 */
void BorrowFromLeft(BTreeNode *curr, BTreeNode *left, int idx) {
    curr->n++;
    for (int i = curr->n - 1; i > idx; i--) {
        curr->keys[i] = curr->keys[i - 1];
    }

    curr->keys[idx] = left->keys[left->n - 1];
    left->n--;

    if (!curr->isLeaf) {
        // Also borrow child pointer
        for (int i = curr->n; i > idx + 1; i--) {
            curr->children[i] = curr->children[i - 1];
        }

        curr->children[idx + 1] = left->children[left->n];
        left->children[left->n] = NULL;
    }
}

/**
 * Borrow a key from right sibling
 * @param curr Current node needing a key
 * @param right Right sibling node
 * @param idx Index position to insert
 */
void BorrowFromRight(BTreeNode *curr, BTreeNode *right, int idx) {
    curr->keys[idx] = right->keys[0];

    for (int i = 0; i < right->n - 1; i++) {
        right->keys[i] = right->keys[i + 1];
    }

    right->n--;

    if (!curr->isLeaf) {
        // Also borrow child pointer
        curr->children[idx + 1] = right->children[0];
        for (int i = 0; i < right->n; i++) {
            right->children[i] = right->children[i + 1];
        }
        right->children[right->n] = NULL;
    }
}

/**
 * Merge current node with left sibling
 * @param curr Current node
 * @param left Left sibling to merge
 * @param idx Index position in parent
 */
void Merge(BTreeNode *curr, BTreeNode *left, int idx) {
    curr->keys[idx - 1] = left->keys[left->n - 1];

    for (int i = 0; i < left->n; i++) {
        curr->keys[idx + i] = left->keys[i];
    }

    for (int i = 0; i <= left->n; i++) {
        curr->children[idx + i] = left->children[i];
    }

    curr->n += (left->n + 1);
    free(left);
}

/**
 * Delete a key from the B-tree (simplified version)
 * @param T Pointer to the B-tree root
 * @param key Key to delete
 */
void BTreeDelete(BTree *T, int key) {
    if (*T == NULL || (*T)->n == 0) {
        return;
    }

    printf("Delete operation (simplified version for B-tree)\n");
}

/**
 * Traverse the B-tree and print its structure
 * @param node Current node
 * @param level Current depth level for printing
 */
void TraverseBTree(BTreeNode *node, int level) {
    if (node == NULL) {
        return;
    }

    printf("Level %d: ", level);
    for (int i = 0; i < node->n; i++) {
        printf("%d ", node->keys[i]);
    }
    printf("\n");

    // Recursively traverse children
    if (!node->isLeaf) {
        for (int i = 0; i <= node->n; i++) {
            TraverseBTree(node->children[i], level + 1);
        }
    }
}
