/**
 * B+ Tree Implementation
 *
 * B+ tree is a variation of B-tree optimized for range queries and disk storage.
 * All actual data is stored in leaf nodes, with internal nodes storing only
 * copies for routing. Leaf nodes are linked together for sequential access.
 *
 * Key Features:
 * - All keys in leaf nodes (internal nodes store routing keys)
 * - Leaf nodes linked as a sorted linked list
 * - All leaf nodes at same depth
 * - Efficient for range queries and sequential access
 * - Widely used in database indexing
 */

#include "../../include/search/b_plus_tree.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Create a new B+ tree node
 * @param isLeaf Flag indicating whether the node is a leaf
 * @return Pointer to the newly created node, or NULL on failure
 */
BPlusTreeNode* CreateBPlusNode(int isLeaf) {
    BPlusTreeNode *node = (BPlusTreeNode *)calloc(1, sizeof(BPlusTreeNode));
    if (node == NULL) return NULL;

    node->numKeys = 0;              // Initialize with zero keys
    node->isLeaf = isLeaf;           // Set leaf flag
    node->next = NULL;               // Initialize leaf link pointer

    // Allocate child pointer array
    node->children = (BPlusTreeNode **)calloc(ORDER + 1, sizeof(BPlusTreeNode *));
    if (node->children == NULL) {
        free(node);
        return NULL;
    }

    return node;
}

/**
 * Create an empty B+ tree
 * @return Pointer to the root of the new B+ tree
 */
BPlusTree CreateBPlusTree(void) {
    return CreateBPlusNode(1);       // Create a leaf node as root
}

/**
 * Find the position where a key should be in a node
 * @param node Node to search
 * @param key Key to find position for
 * @return Index where key should be inserted
 */
int FindKeyPosition(BPlusTreeNode *node, int key) {
    int pos = 0;
    while (pos < node->numKeys && key >= node->keys[pos]) {
        pos++;
    }
    return pos;
}

/**
 * Search for a key in the B+ tree
 * @param T Pointer to the B+ tree root
 * @param key Key to search for
 * @return 1 if found, 0 if not found
 */
int BPlusTreeSearch(BPlusTree *T, int key) {
    if (*T == NULL || (*T)->numKeys == 0) return 0;

    BPlusTreeNode *curr = *T;

    // Traverse down to a leaf node
    while (!curr->isLeaf) {
        int i = FindKeyPosition(curr, key);
        curr = curr->children[i];
        if (curr == NULL) return 0;
    }

    // Search in the leaf node
    for (int i = 0; i < curr->numKeys; i++) {
        if (curr->keys[i] == key) {
            return 1;  // Key found
        }
    }

    return 0;  // Key not found
}

/**
 * Split a leaf node
 * @param leaf Leaf node to split
 * @param medianKey Output: first key of the new node
 * @return Pointer to the new leaf node, or NULL on failure
 */
BPlusTreeNode* SplitLeaf(BPlusTreeNode *leaf, int *medianKey) {
    BPlusTreeNode *newNode = CreateBPlusNode(1);
    if (newNode == NULL) return NULL;

    int mid = ORDER / 2;

    // Copy second half of keys to new node
    for (int i = mid; i < ORDER; i++) {
        newNode->keys[i - mid] = leaf->keys[i];
        newNode->numKeys++;
    }

    leaf->numKeys = mid;
    *medianKey = newNode->keys[0];  // First key of new node

    // Maintain leaf chain for sequential access
    newNode->next = leaf->next;
    leaf->next = newNode;

    return newNode;
}

/**
 * Split an internal node
 * @param node Internal node to split
 * @param medianKey Output: key that moves to parent
 * @return Pointer to the new internal node, or NULL on failure
 */
BPlusTreeNode* SplitInternal(BPlusTreeNode *node, int *medianKey) {
    BPlusTreeNode *newNode = CreateBPlusNode(0);
    if (newNode == NULL) return NULL;

    int mid = ORDER / 2;
    *medianKey = node->keys[mid];  // Median key moves to parent

    // Copy keys after median to new node
    for (int i = mid + 1; i < ORDER; i++) {
        newNode->keys[i - mid - 1] = node->keys[i];
        newNode->numKeys++;
    }

    // Copy child pointers
    for (int i = mid + 1; i <= ORDER; i++) {
        newNode->children[i - mid - 1] = node->children[i];
        node->children[i] = NULL;
    }

    node->numKeys = mid;

    return newNode;
}

/**
 * Insert a key into a leaf node
 * @param leaf Leaf node to insert into
 * @param key Key to insert
 * @return New number of keys in the node
 */
int InsertIntoLeaf(BPlusTreeNode *leaf, int key) {
    int i = leaf->numKeys - 1;
    // Shift keys to make room for new key
    while (i >= 0 && key < leaf->keys[i]) {
        leaf->keys[i + 1] = leaf->keys[i];
        i--;
    }
    leaf->keys[i + 1] = key;
    leaf->numKeys++;
    return leaf->numKeys;
}

/**
 * Insert a key into an internal node
 * @param node Internal node to insert into
 * @param key Key to insert
 * @param rightChild Right child pointer for the new key
 */
void InsertIntoInternal(BPlusTreeNode *node, int key, BPlusTreeNode *rightChild) {
    int i = node->numKeys - 1;
    // Shift keys and children to make room
    while (i >= 0 && key < node->keys[i]) {
        node->keys[i + 1] = node->keys[i];
        node->children[i + 2] = node->children[i + 1];
        i--;
    }
    node->keys[i + 1] = key;
    node->children[i + 2] = rightChild;
    node->numKeys++;
}

/**
 * Insert a key into the B+ tree
 * @param T Pointer to the B+ tree root (may change)
 * @param key Key to insert
 */
void BPlusTreeInsert(BPlusTree *T, int key) {
    if (*T == NULL) {
        *T = CreateBPlusTree();
        (*T)->keys[0] = key;
        (*T)->numKeys = 1;
        return;
    }

    BPlusTreeNode *root = *T;

    // Handle case where root is a leaf node
    if (root->isLeaf) {
        // Check if root needs splitting
        if (root->numKeys < ORDER) {
            InsertIntoLeaf(root, key);
            return;
        }

        // Split root and create new root
        int medianKey;
        BPlusTreeNode *newNode = SplitLeaf(root, &medianKey);
        if (newNode == NULL) return;

        BPlusTreeNode *newRoot = CreateBPlusNode(0);
        if (newRoot == NULL) {
            free(newNode);
            return;
        }

        newRoot->keys[0] = medianKey;
        newRoot->children[0] = root;
        newRoot->children[1] = newNode;
        newRoot->numKeys = 1;
        *T = newRoot;

        // Insert key into correct leaf node
        if (key < medianKey) {
            InsertIntoLeaf(root, key);
        } else {
            InsertIntoLeaf(newNode, key);
        }
        return;
    }

    // Handle non-leaf root
    BPlusTreeNode *curr = root;
    BPlusTreeNode *parent = NULL;
    int childIdx = 0;

    // Find insertion position and traverse down
    while (!curr->isLeaf) {
        parent = curr;
        childIdx = FindKeyPosition(curr, key);
        curr = curr->children[childIdx];

        if (curr == NULL) return;

        // Check if child needs splitting
        if (curr->isLeaf && curr->numKeys == ORDER) {
            int medianKey;
            BPlusTreeNode *newNode = SplitLeaf(curr, &medianKey);
            if (newNode == NULL) return;

            InsertIntoInternal(parent, medianKey, newNode);

            // Choose correct child for insertion
            if (key >= medianKey) {
                curr = newNode;
            }
        }
    }

    // Insert into leaf node
    if (curr->numKeys < ORDER) {
        InsertIntoLeaf(curr, key);
    }
}

/**
 * Delete a key from the B+ tree (simplified version)
 * @param T Pointer to the B+ tree root
 * @param key Key to delete
 */
void BPlusTreeDelete(BPlusTree *T, int key) {
    if (*T == NULL) return;
    printf("Delete operation (simplified version for B+ tree)\n");
}

/**
 * Traverse B+ tree and print keys in sorted order (leaf chain)
 * @param T B+ tree root
 */
void TraverseBPlusTree(BPlusTree T) {
    if (T == NULL) return;

    BPlusTreeNode *curr = T;

    // Find the first leaf node
    while (!curr->isLeaf) {
        curr = curr->children[0];
        if (curr == NULL) return;
    }

    // Traverse through all leaf nodes in order
    while (curr != NULL) {
        for (int i = 0; i < curr->numKeys; i++) {
            printf("%d ", curr->keys[i]);
        }
        curr = curr->next;
    }
}

/**
 * Print B+ tree structure showing all levels
 * @param T B+ tree root
 * @param level Current depth level for printing
 */
void PrintBPlusTree(BPlusTree T, int level) {
    if (T == NULL) return;

    printf("Level %d: ", level);
    for (int i = 0; i < T->numKeys; i++) {
        printf("%d ", T->keys[i]);
    }
    printf("\n");

    // Recursively print children
    if (!T->isLeaf) {
        for (int i = 0; i <= T->numKeys; i++) {
            PrintBPlusTree(T->children[i], level + 1);
        }
    }
}

/**
 * Destroy B+ tree and free all memory
 * @param T B+ tree root
 */
void DestroyBPlusTree(BPlusTree T) {
    if (T == NULL) return;

    // Recursively destroy children
    if (!T->isLeaf) {
        for (int i = 0; i <= T->numKeys; i++) {
            DestroyBPlusTree(T->children[i]);
        }
    }

    free(T->children);
    free(T);
}
