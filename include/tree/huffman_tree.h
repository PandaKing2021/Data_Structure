#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

typedef struct {
    int weight;
    int parent, lchild, rchild;
} HTNode, *HuffmanTree;

typedef char **HuffmanCode;

void CreateHuffmanTree(HuffmanTree *HT, int *w, int n);
void CreateHuffmanCode(HuffmanTree HT, HuffmanCode *HC, int n);
void PrintHuffmanCode(HuffmanCode HC, int *w, int n);

#endif
