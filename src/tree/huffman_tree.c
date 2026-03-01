#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/tree/huffman_tree.h"

void Select(HuffmanTree HT, int n, int *s1, int *s2) {
    int min1 = 9999, min2 = 9999;
    *s1 = *s2 = 0;
    for (int i = 1; i <= n; i++) {
        if (HT[i].parent == 0) {
            if (HT[i].weight < min1) {
                min2 = min1;
                *s2 = *s1;
                min1 = HT[i].weight;
                *s1 = i;
            } else if (HT[i].weight < min2) {
                min2 = HT[i].weight;
                *s2 = i;
            }
        }
    }
}

void CreateHuffmanTree(HuffmanTree *HT, int *w, int n) {
    if (n <= 1) return;
    int m = 2 * n - 1;
    *HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
    for (int i = 1; i <= n; i++) {
        (*HT)[i].weight = w[i - 1];
        (*HT)[i].parent = (*HT)[i].lchild = (*HT)[i].rchild = 0;
    }
    for (int i = n + 1; i <= m; i++) {
        (*HT)[i].weight = (*HT)[i].parent = (*HT)[i].lchild = (*HT)[i].rchild = 0;
    }
    for (int i = n + 1; i <= m; i++) {
        int s1, s2;
        Select(*HT, i - 1, &s1, &s2);
        (*HT)[s1].parent = (*HT)[s2].parent = i;
        (*HT)[i].lchild = s1;
        (*HT)[i].rchild = s2;
        (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
    }
}

void CreateHuffmanCode(HuffmanTree HT, HuffmanCode *HC, int n) {
    *HC = (HuffmanCode)malloc(n * sizeof(char *));
    char *cd = (char *)malloc(n * sizeof(char));
    cd[n - 1] = '\0';
    for (int i = 1; i <= n; i++) {
        int start = n - 1;
        int c = i, f = HT[i].parent;
        while (f != 0) {
            --start;
            if (HT[f].lchild == c) cd[start] = '0';
            else cd[start] = '1';
            c = f;
            f = HT[f].parent;
        }
        (*HC)[i - 1] = (char *)malloc((n - start) * sizeof(char));
        strcpy((*HC)[i - 1], &cd[start]);
    }
    free(cd);
}

void PrintHuffmanCode(HuffmanCode HC, int *w, int n) {
    for (int i = 0; i < n; i++) {
        printf("Weight %d: %s\n", w[i], HC[i]);
    }
}
