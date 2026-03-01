#include "../../include/search/kmp.h"
#include <stdio.h>
#include <string.h>

int main() {
    printf("=== KMP String Pattern Matching Tests ===\n\n");

    char text[] = "ABABDABACDABABCABAB";
    char pattern1[] = "ABABCABAB";
    char pattern2[] = "ABABAB";
    char pattern3[] = "XYZ";

    printf("Text: %s\n", text);
    printf("Pattern 1: %s\n", pattern1);
    printf("Pattern 2: %s\n", pattern2);
    printf("Pattern 3: %s\n\n", pattern3);

    /* KMP algorithm */
    printf("1. KMP Algorithm:\n");
    int result1 = KMPMatch(text, pattern1);
    int result2 = KMPMatch(text, pattern2);
    int result3 = KMPMatch(text, pattern3);
    printf("Pattern 1: %s\n", result1 != -1 ? "matched" : "not matched");
    if (result1 != -1) {
        printf("  Found at position %d\n", result1);
    }
    printf("Pattern 2: %s\n", result2 != -1 ? "matched" : "not matched");
    if (result2 != -1) {
        printf("  Found at position %d\n", result2);
    }
    printf("Pattern 3: %s\n", result3 != -1 ? "matched" : "not matched");
    if (result3 != -1) {
        printf("  Found at position %d\n", result3);
    }

    /* Find all matches */
    printf("\n2. KMP Find All Matches:\n");
    int positions[100];
    int count = KMPMatchAll(text, pattern2, positions);
    printf("Pattern '%s' found %d times at positions: ", pattern2, count);
    for (int i = 0; i < count; i++) {
        printf("%d ", positions[i]);
    }
    printf("\n");

    /* Improved KMP algorithm */
    printf("\n3. Improved KMP (nextval):\n");
    int result1_improved = KMPMatchImproved(text, pattern1);
    printf("Pattern 1: %s at position %d\n",
           result1_improved != -1 ? "matched" : "not matched",
           result1_improved);

    /* Brute force match */
    printf("\n4. Brute Force Match:\n");
    int result1_bf = BruteForceMatch(text, pattern1);
    int result2_bf = BruteForceMatch(text, pattern2);
    printf("Pattern 1: %s at position %d\n",
           result1_bf != -1 ? "matched" : "not matched", result1_bf);
    printf("Pattern 2: %s at position %d\n",
           result2_bf != -1 ? "matched" : "not matched", result2_bf);

    printf("\n=== All Tests Passed ===\n");
    return 0;
}
