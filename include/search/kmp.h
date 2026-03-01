/**
 * KMP (Knuth-Morris-Pratt) String Matching Algorithm
 *
 * KMP is an efficient string matching algorithm that pre-processes the
 * pattern to avoid unnecessary comparisons during matching.
 *
 * Time Complexity: O(n + m) where n = text length, m = pattern length
 * Space Complexity: O(m) for the next/nextval array
 *
 * Advantages over naive approach:
 * - No backtracking in text string
 * - Efficient for patterns with repeated prefixes
 * - Guaranteed linear time complexity
 */

#ifndef KMP_H
#define KMP_H

/**
 * Maximum pattern length supported
 */
#define MAX_PATTERN_LEN 1000

/**
 * Compute the Next array (failure function) for KMP algorithm
 * Next[i] = length of longest proper prefix which is also suffix of pattern[0..i]
 *
 * @param pattern Pattern string to process
 * @param next Output array for failure function values
 * @param m Length of pattern string
 */
void ComputeNext(char pattern[], int next[], int m);

/**
 * KMP string matching algorithm
 * Searches for pattern in text using the failure function
 *
 * @param text Text string to search in
 * @param pattern Pattern string to find
 * @return Index of first match (0-based), or -1 if not found
 */
int KMPMatch(char text[], char pattern[]);

/**
 * KMP algorithm to find all occurrences
 * Searches for all positions where pattern occurs in text
 *
 * @param text Text string to search in
 * @param pattern Pattern string to find
 * @param positions Array to store match positions
 * @return Number of matches found
 */
int KMPMatchAll(char text[], char pattern[], int positions[]);

/**
 * Compute optimized Nextval array
 * Nextval is an optimized version that handles the case where
 * pattern[i] == pattern[next[i]] to reduce redundant comparisons
 *
 * @param pattern Pattern string to process
 * @param nextval Output array for optimized failure function
 * @param m Length of pattern string
 */
void ComputeNextVal(char pattern[], int nextval[], int m);

/**
 * Improved KMP algorithm using Nextval array
 * Same functionality as KMPMatch but with optimized nextval array
 *
 * @param text Text string to search in
 * @param pattern Pattern string to find
 * @return Index of first match (0-based), or -1 if not found
 */
int KMPMatchImproved(char text[], char pattern[]);

/**
 * Brute force (naive) string matching algorithm
 * Compares pattern with every possible starting position
 *
 * Time Complexity: O(n * m) - used for comparison/testing
 *
 * @param text Text string to search in
 * @param pattern Pattern string to find
 * @return Index of first match (0-based), or -1 if not found
 */
int BruteForceMatch(char text[], char pattern[]);

#endif
