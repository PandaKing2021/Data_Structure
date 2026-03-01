/**
 * Stack Applications Header
 *
 * This module demonstrates various practical applications of stack data
 * structure. Stack follows LIFO (Last In First Out) principle, making it
 * ideal for problems requiring backtracking or reversing order.
 *
 * Applications Covered:
 * 1. Bracket Matching: Validate nested brackets, parentheses, and braces
 * 2. Expression Evaluation: Convert infix to postfix, evaluate postfix expressions
 * 3. Recursion Simulation: Use stack to simulate recursive function calls
 *
 * Common Stack Operations Used:
 * - Push: Add element to top of stack
 * - Pop: Remove element from top of stack
 * - Peek/Top: View top element without removing
 * - IsEmpty: Check if stack is empty
 */

#ifndef STACK_APPLICATIONS_H
#define STACK_APPLICATIONS_H

#include "../stack_queue/seq_stack.h"

/**
 * Maximum expression length supported
 */
#define MAX_EXPR_LEN 100

// ============================================================================
// Bracket Matching
// ============================================================================

/**
 * Check if brackets in a string are properly matched and nested
 * Supports: (), {}, []
 *
 * Algorithm:
 * - Push opening brackets onto stack
 * - Pop when closing bracket matches top of stack
 * - Return failure if mismatch or stack not empty at end
 *
 * @param str String to check for bracket matching
 * @return 1 if brackets are matched, 0 if mismatched
 */
int BracketMatching(char *str);

// ============================================================================
// Expression Conversion and Evaluation
// ============================================================================

/**
 * Convert infix expression to postfix (Reverse Polish Notation)
 * Postfix notation eliminates need for parentheses and operator precedence
 *
 * Example: "a+b*c" becomes "abc*+"
 *
 * @param infix Infix expression string
 * @param postfix Output buffer for postfix expression
 * @return 1 if conversion successful, 0 if failed
 */
int InfixToPostfix(char *infix, char *postfix);

/**
 * Get precedence (priority) of an operator
 * Higher value means higher precedence
 *
 * @param op Operator character (+, -, *, /, ^)
 * @return Precedence value
 */
int GetPriority(char op);

/**
 * Check if character is an operator
 * @param c Character to check
 * @return 1 if operator, 0 otherwise
 */
int IsOperator(char c);

/**
 * Check if character is an operand (number or letter)
 * @param c Character to check
 * @return 1 if operand, 0 otherwise
 */
int IsOperand(char c);

/**
 * Evaluate a postfix expression using a stack
 * Postfix evaluation is straightforward using a stack:
 * - Push operands onto stack
 * - Pop operands when operator encountered
 * - Push result back onto stack
 *
 * @param postfix Postfix expression string
 * @return Result of expression evaluation
 */
int EvaluatePostfix(char *postfix);

// ============================================================================
// Recursion Simulation Using Stack
// ============================================================================

/**
 * Calculate factorial using stack to simulate recursion
 * Factorial(n) = n * (n-1) * ... * 1
 *
 * @param n Positive integer
 * @return Factorial of n
 */
int FactorialWithStack(int n);

/**
 * Calculate Fibonacci number using stack to simulate recursion
 * Fibonacci(n) = Fibonacci(n-1) + Fibonacci(n-2)
 * Base cases: Fibonacci(0) = 0, Fibonacci(1) = 1
 *
 * @param n Positive integer
 * @return nth Fibonacci number
 */
int FibonacciWithStack(int n);

/**
 * Solve Tower of Hanoi problem using stack to simulate recursion
 * Move n disks from 'from' peg to 'to' peg using 'aux' as auxiliary
 *
 * Rules:
 * - Only one disk can be moved at a time
 * - A disk can only be moved from top of one peg to top of another
 * - No disk can be placed on top of a smaller disk
 *
 * @param n Number of disks
 * @param from Source peg
 * @param aux Auxiliary peg
 * @param to Destination peg
 */
void HanoiWithStack(int n, char from, char aux, char to);

#endif
