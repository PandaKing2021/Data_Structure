/**
 * KMP (Knuth-Morris-Pratt) String Matching Algorithm Implementation
 *
 * KMP is an efficient string matching algorithm that avoids unnecessary
 * comparisons by using information from partial matches. It pre-processes
 * the pattern to build a failure function that indicates how much to skip
 * when a mismatch occurs.
 *
 * Time Complexity:
 * - Preprocessing: O(m) where m is pattern length
 * - Matching: O(n) where n is text length
 * - Total: O(n + m), much better than naive O(n*m)
 */

#include "../../include/search/kmp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Compute the Next array for KMP algorithm
 * Next[i] stores the length of the longest proper prefix which is also
 * a suffix for pattern[0...i]
 *
 * @param pattern Pattern string to process
 * @param next Output array for failure function values
 * @param len Length of pattern
 */
void GetNext(char pattern[], int next[], int len) {
    next[0] = -1;           // First character has no proper prefix
    int i = 0;              // Current position in pattern
    int j = -1;             // Length of current matching prefix/suffix

    while (i < len) {
        if (j == -1 || pattern[i] == pattern[j]) {
            i++;
            j++;
            next[i] = j;
        } else {
            j = next[j];    // Fall back to shorter prefix
        }
    }
}

/**
 * Compute the Nextval array (optimized version of Next)
 * Nextval handles the case where pattern[i] == pattern[next[i]]
 * to avoid unnecessary comparisons
 *
 * @param pattern Pattern string to process
 * @param nextval Output array for optimized failure function values
 * @param len Length of pattern
 */
void GetNextval(char pattern[], int nextval[], int len) {
    nextval[0] = -1;
    int i = 0;
    int j = -1;

    while (i < len) {
        if (j == -1 || pattern[i] == pattern[j]) {
            i++;
            j++;
            if (pattern[i] != pattern[j]) {
                nextval[i] = j;
            } else {
                nextval[i] = nextval[j];
            }
        } else {
            j = nextval[j];
        }
    }
}

/**
 * KMP string matching using Next array
 * Searches for pattern in text using the failure function
 *
 * @param text Text string to search in
 * @param pattern Pattern string to find
 * @return Index of first occurrence, or -1 if not found
 */
int KMP(char text[], char pattern[]) {
    int i = 0;              // Index in text
    int j = 0;              // Index in pattern
    int lenText = strlen(text);
    int lenPattern = strlen(pattern);

    int *next = (int *)malloc(lenPattern * sizeof(int));
    if (next == NULL) return -1;

    GetNext(pattern, next, lenPattern);

    while (i < lenText && j < lenPattern) {
        if (j == -1 || text[i] == pattern[j]) {
            i++;
            j++;
        } else {
            j = next[j];    // Skip using next array
        }
    }

    free(next);

    if (j == lenPattern) {
        return i - j;       // Pattern found
    } else {
        return -1;          // Pattern not found
    }
}

/**
 * KMP string matching using Nextval array (optimized)
 * Same as KMP but uses the optimized nextval array
 *
 * @param text Text string to search in
 * @param pattern Pattern string to find
 * @return Index of first occurrence, or -1 if not found
 */
int KMPNextval(char text[], char pattern[]) {
    int i = 0;
    int j = 0;
    int lenText = strlen(text);
    int lenPattern = strlen(pattern);

    int *nextval = (int *)malloc(lenPattern * sizeof(int));
    if (nextval == NULL) return -1;

    GetNextval(pattern, nextval, lenPattern);

    while (i < lenText && j < lenPattern) {
        if (j == -1 || text[i] == pattern[j]) {
            i++;
            j++;
        } else {
            j = nextval[j];
        }
    }

    free(nextval);

    if (j == lenPattern) {
        return i - j;
    } else {
        return -1;
    }
}

/**
 * Find all occurrences of pattern in text using KMP
 * Prints all starting positions where pattern is found
 *
 * @param text Text string to search in
 * @param pattern Pattern string to find
 */
void KMPFindAll(char text[], char pattern[]) {
    int i = 0;
    int j = 0;
    int lenText = strlen(text);
    int lenPattern = strlen(pattern);
    int count = 0;

    int *next = (int *)malloc(lenPattern * sizeof(int));
    if (next == NULL) return;

    GetNext(pattern, next, lenPattern);

    while (i < lenText) {
        if (j == -1 || text[i] == pattern[j]) {
            i++;
            j++;

            if (j == lenPattern) {
                printf("Pattern found at position %d\n", i - j);
                count++;
                j = next[j];    // Continue searching for more occurrences
            }
        } else {
            j = next[j];
        }
    }

    printf("Total occurrences: %d\n", count);
    free(next);
}

/**
 * Naive brute-force string matching (for comparison)
 * Compares pattern with every possible position in text
 *
 * @param text Text string to search in
 * @param pattern Pattern string to find
 * @return Index of first occurrence, or -1 if not found
 */
int BruteForce(char text[], char pattern[]) {
    int i = 0;
    int j = 0;
    int lenText = strlen(text);
    int lenPattern = strlen(pattern);

    while (i < lenText && j < lenPattern) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        } else {
            i = i - j + 1;      // Move to next position
            j = 0;              // Reset pattern index
        }
    }

    if (j == lenPattern) {
        return i - j;
    } else {
        return -1;
    }
}
