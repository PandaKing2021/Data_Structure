#include "../../include/sort/external_sort.h"
#include <stdio.h>
#include <stdlib.h>

// 创建测试数据文件
void CreateTestFile(const char *filename, int size) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Cannot create test file\n");
        return;
    }

    srand(100);
    for (int i = 0; i < size; i++) {
        int num = rand() % 10000;
        fwrite(&num, sizeof(int), 1, file);
    }

    fclose(file);
    printf("Created test file: %s (%d numbers)\n", filename, size);
}

// 验证排序结果
int VerifySorted(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return 0;
    }

    int prev, curr;
    int count = fread(&prev, sizeof(int), 1, file);
    int isSorted = 1;

    while (fread(&curr, sizeof(int), 1, file) > 0) {
        if (curr < prev) {
            isSorted = 0;
            break;
        }
        prev = curr;
        count++;
    }

    fclose(file);
    return isSorted;
}

int main() {
    printf("=== External Sort Tests ===\n\n");

    // 测试1：小数据集
    printf("Test 1: Small dataset (100 numbers)\n");
    CreateTestFile("input_small.txt", 100);
    ExternalSort("input_small.txt", "output_small.txt");

    if (VerifySorted("output_small.txt")) {
        printf("Small dataset: VERIFIED SORTED ✓\n");
    } else {
        printf("Small dataset: NOT SORTED ✗\n");
    }

    // 测试2：中等数据集
    printf("\nTest 2: Medium dataset (500 numbers)\n");
    CreateTestFile("input_medium.txt", 500);
    ExternalSort("input_medium.txt", "output_medium.txt");

    if (VerifySorted("output_medium.txt")) {
        printf("Medium dataset: VERIFIED SORTED ✓\n");
    } else {
        printf("Medium dataset: NOT SORTED ✗\n");
    }

    // 测试3：大数据集
    printf("\nTest 3: Large dataset (2000 numbers)\n");
    CreateTestFile("input_large.txt", 2000);
    ExternalSort("input_large.txt", "output_large.txt");

    if (VerifySorted("output_large.txt")) {
        printf("Large dataset: VERIFIED SORTED ✓\n");
    } else {
        printf("Large dataset: NOT SORTED ✗\n");
    }

    // 测试4：已排序数据
    printf("\nTest 4: Already sorted data\n");
    CreateTestFile("input_sorted.txt", 100);

    // 手动创建已排序文件
    FILE *file = fopen("input_sorted.txt", "w");
    if (file) {
        for (int i = 0; i < 100; i++) {
            int num = i * 10;
            fwrite(&num, sizeof(int), 1, file);
        }
        fclose(file);
    }

    ExternalSort("input_sorted.txt", "output_sorted.txt");

    if (VerifySorted("output_sorted.txt")) {
        printf("Already sorted: VERIFIED ✓\n");
    } else {
        printf("Already sorted: FAILED ✗\n");
    }

    printf("\n=== All Tests Completed ===\n");
    return 0;
}
