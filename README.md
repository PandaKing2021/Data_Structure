# Data Structures Implementation

This project implements common data structures and algorithms based on the Computer Science Professional Foundation Exam syllabus using pure C language.

## Directory Structure

### include/
Header files containing data structure declarations.

#### linear_list/
- `seq_list.h` - Sequential list (array-based implementation)
- `link_list.h` - Singly linked list
- `double_link_list.h` - Doubly linked list
- `multi_array.h` - Multi-dimensional array
- `sparse_matrix.h` - Sparse matrix (Triplet and Cross List)
- `special_matrix.h` - Special matrices (Symmetric, Triangular, Tridiagonal)

#### stack_queue/
- `seq_stack.h` - Sequential stack
- `link_stack.h` - Linked stack
- `seq_queue.h` - Sequential queue (circular buffer)
- `link_queue.h` - Linked queue
- `stack_applications.h` - Stack applications (bracket matching, expression evaluation)

#### tree/
- `binary_tree.h` - Binary tree with traversal operations
- `disjoint_set.h` - Disjoint set (Union-Find)
- `heap.h` - Max heap and Min heap
- `huffman_tree.h` - Huffman tree with encoding

#### graph/
- `matrix_graph.h` - Graph using adjacency matrix
- `adj_list_graph.h` - Graph using adjacency list
- `multilist_graph.h` - Adjacency multilist graph
- `orthogonal_list_graph.h` - Orthogonal list (cross list) graph

#### search/
- `sequential_search.h` - Sequential search
- `block_search.h` - Block search
- `binary_search_tree.h` - Binary search tree (BST)
- `avl_tree.h` - AVL tree (self-balancing BST)
- `red_black_tree.h` - Red-Black tree
- `b_tree.h` - B tree
- `b_plus_tree.h` - B+ tree
- `hash_table.h` - Hash table
- `kmp.h` - KMP string pattern matching

#### sort/
- `insert_sort.h` - Insertion sort and binary insertion sort
- `bubble_sort.h` - Bubble sort
- `selection_sort.h` - Selection sort
- `shell_sort.h` - Shell sort
- `quick_sort.h` - Quick sort
- `heap_sort.h` - Heap sort
- `merge_sort.h` - Merge sort
- `radix_sort.h` - Radix sort
- `external_sort.h` - External sort

---

### src/
Source files containing implementations of all data structures and algorithms.

#### linear_list/
- `seq_list.c` - Sequential list with insert, delete, search
- `link_list.c` - Singly linked list
- `double_link_list.c` - Doubly linked list
- `multi_array.c` - Multi-dimensional array operations
- `sparse_matrix.c` - Sparse matrix (Triplet and Cross List)
- `special_matrix.c` - Special matrices compression storage

#### stack_queue/
- `seq_stack.c` - Sequential stack (push, pop, getTop)
- `link_stack.c` - Linked stack
- `seq_queue.c` - Circular queue
- `link_queue.c` - Linked queue
- `stack_applications.c` - Stack applications:
  - Bracket matching
  - Infix to postfix conversion
  - Postfix expression evaluation
  - Factorial simulation with stack
  - Fibonacci simulation with stack
  - Tower of Hanoi

#### tree/
- `binary_tree.c` - Binary tree with:
  - Preorder, Inorder, Postorder, Level-order traversals
  - Tree depth, node count, leaf count
  - Threaded binary tree
- `disjoint_set.c` - Union-Find operations
- `heap.c` - Max heap and Min heap with insert, delete, heapify
- `huffman_tree.c` - Huffman tree construction and encoding

#### graph/
- `matrix_graph.c` - Adjacency matrix graph with:
  - DFS and BFS traversals
  - Prim's and Kruskal's MST algorithms
  - Dijkstra's shortest path
  - Floyd-Warshall all-pairs shortest paths
  - Topological sort
  - Critical path (AOE network)
- `adj_list_graph.c` - Adjacency list graph with DFS and BFS
- `multilist_graph.c` - Adjacency multilist for undirected graphs
- `orthogonal_list_graph.c` - Orthogonal list for directed graphs

#### search/
- `sequential_search.c` - Sequential search with count and sentinel
- `block_search.c` - Block search with optional binary search
- `binary_search_tree.c` - BST with insert, search, delete
- `avl_tree.c` - AVL tree with rotations
- `red_black_tree.c` - Red-Black tree
- `b_tree.c` - B tree operations
- `b_plus_tree.c` - B+ tree operations
- `hash_table.h` - Hash table with linear probing
- `kmp.c` - KMP and improved KMP (nextval), brute force

#### sort/
All sorting algorithms with 0-based array indexing:
- `insert_sort.c` - Insertion sort and binary insertion sort
- `bubble_sort.c` - Bubble sort with optimization
- `selection_sort.c` - Selection sort
- `shell_sort.c` - Shell sort
- `quick_sort.c` - Quick sort with partition
- `heap_sort.c` - Heap sort
- `merge_sort.c` - Merge sort (divide and conquer)
- `radix_sort.c` - Radix sort for non-negative integers
- `external_sort.c` - External sort for large files

---

### tests/
Test programs for each data structure module.

#### linear_list/
- `test_seq_list.c` - Sequential list operations
- `test_link_list.c` - Linked list operations
- `test_multi_array.c` - Multi-dimensional array
- `test_sparse_matrix.c` - Sparse matrix (Triplet and Cross List)
- `test_special_matrix.c` - Special matrix compression

#### stack_queue/
- `test_stack.c` - Stack operations
- `test_queue.c` - Queue operations
- `test_stack_applications.c` - Stack applications

#### tree/
- `test_binary_tree.c` - Binary tree traversals
- `test_heap.c` - Heap operations
- `test_huffman_tree.c` - Huffman coding

#### graph/
- `test_matrix_graph.c` - Matrix graph operations
- `test_adj_list_graph.c` - Adjacency list graph
- `test_multilist_graph.c` - Multilist graph
- `test_orthogonal_list_graph.c` - Orthogonal list graph

#### search/
- `test_sequential_search.c` - Sequential search
- `test_block_search.c` - Block search
- `test_bst.c` - Binary search tree
- `test_avl.c` - AVL tree
- `test_red_black_tree.c` - Red-Black tree
- `test_b_tree.c` - B tree
- `test_b_plus_tree.c` - B+ tree
- `test_hash.c` - Hash table
- `test_kmp.c` - KMP string matching

#### sort/
- `test_sort.c` - All sorting algorithms
- `test_external_sort.c` - External sorting

---

## Building and Running

### Build all modules:
```bash
build_all.bat
```

### Quick test:
```bash
quick_test.bat
```

### Build and run individual module:
```bash
# Linear list
gcc -I. -o test_seq_list.exe src/linear_list/seq_list.c tests/linear_list/test_seq_list.c
test_seq_list.exe

# Sort algorithms
gcc -I. -o test_sort.exe src/sort/*.c tests/sort/test_sort.c
test_sort.exe
```

