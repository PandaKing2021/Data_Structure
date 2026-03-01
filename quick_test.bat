@echo off
echo ========================================
echo Quick Data Structures Tests
echo ========================================

echo.
echo [1/10] Sequential List...
gcc -I. -o test_seq_list.exe src/linear_list/seq_list.c tests/linear_list/test_seq_list.c && test_seq_list.exe

echo.
echo [2/10] Linked List...
gcc -I. -o test_link_list.exe src/linear_list/link_list.c tests/linear_list/test_link_list.c && test_link_list.exe

echo.
echo [3/10] Stack...
gcc -I. -o test_stack.exe src/stack_queue/seq_stack.c src/stack_queue/link_stack.c tests/stack_queue/test_stack.c && test_stack.exe

echo.
echo [4/10] Queue...
gcc -I. -o test_queue.exe src/stack_queue/seq_queue.c src/stack_queue/link_queue.c tests/stack_queue/test_queue.c && test_queue.exe

echo.
echo [5/10] BST...
gcc -I. -o test_bst.exe src/search/binary_search_tree.c tests/search/test_bst.c && test_bst.exe

echo.
echo [6/10] AVL Tree...
gcc -I. -o test_avl.exe src/search/avl_tree.c tests/search/test_avl.c && test_avl.exe

echo.
echo [7/10] Hash Table...
gcc -I. -o test_hash.exe src/search/hash_table.c tests/search/test_hash.c && test_hash.exe

echo.
echo [8/10] Heap...
gcc -I. -o test_heap.exe src/tree/heap.c tests/tree/test_heap.c && test_heap.exe

echo.
echo [9/10] Graph (sample data)...
echo 5 7 > graph_input.txt
echo 1 2 3 4 5 >> graph_input.txt
echo 1 2 4 >> graph_input.txt
echo 1 3 2 >> graph_input.txt
echo 2 3 1 >> graph_input.txt
echo 2 4 5 >> graph_input.txt
echo 3 4 8 >> graph_input.txt
echo 3 5 10 >> graph_input.txt
echo 4 5 2 >> graph_input.txt
gcc -I. -o test_matrix_graph.exe src/graph/matrix_graph.c tests/graph/test_matrix_graph.c && test_matrix_graph.exe < graph_input.txt
del graph_input.txt

echo.
echo [10/10] Sorting Algorithms...
gcc -I. -o test_sort.exe src/sort/*.c tests/sort/test_sort.c && test_sort.exe

echo.
echo ========================================
echo Quick Tests Completed!
echo ========================================
