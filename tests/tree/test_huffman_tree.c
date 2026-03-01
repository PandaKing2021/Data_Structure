#include <stdio.h>
#include <stdlib.h>
#include "include/tree/huffman_tree.h"

int main() {
    printf("=== Huffman Tree Test ===\n");

    int n;
    printf("Enter number of weights: ");
    scanf("%d", &n);

    int *weights = (int *)malloc(n * sizeof(int));
    printf("Enter weights: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &weights[i]);
    }

    HuffmanTree HT;
    HuffmanCode HC;

    CreateHuffmanTree(&HT, weights, n);
    CreateHuffmanCode(HT, &HC, n);

    printf("\nHuffman Codes:\n");
    PrintHuffmanCode(HC, weights, n);

    free(weights);
    free(HT);
    for (int i = 0; i < n; i++) {
        free(HC[i]);
    }
    free(HC);

    return 0;
}
