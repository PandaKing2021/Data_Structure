#include "../../include/stack_queue/stack_applications.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* ==================== Bracket Matching ==================== */

/**
 * Check if brackets are balanced in a string.
 * Supports parentheses (), brackets [], and braces {}.
 * @param str The input string to check
 * @return 1 if balanced, 0 otherwise
 */
int BracketMatching(char *str) {
    SeqStack S;
    InitStack(&S);

    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        if (c == '(' || c == '[' || c == '{') {
            Push(&S, (int)c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (StackEmpty(S)) {
                return 0;
            }

            int top;
            GetTop(S, &top);
            Pop(&S, &top);

            if ((c == ')' && (char)top != '(') ||
                (c == ']' && (char)top != '[') ||
                (c == '}' && (char)top != '{')) {
                return 0;
            }
        }
    }

    return StackEmpty(S) ? 1 : 0;
}

/* ==================== Expression Conversion and Evaluation ==================== */

/**
 * Get the priority of an operator.
 * @param op The operator character
 * @return Priority value (higher means higher precedence)
 */
int GetPriority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

/**
 * Check if a character is an operator.
 * @param c The character to check
 * @return 1 if operator, 0 otherwise
 */
int IsOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

/**
 * Check if a character is an operand (alphanumeric).
 * @param c The character to check
 * @return 1 if operand, 0 otherwise
 */
int IsOperand(char c) {
    return isalnum(c);
}

/**
 * Convert infix expression to postfix expression.
 * @param infix The infix expression string
 * @param postfix The output postfix expression string
 * @return 1 on success
 */
int InfixToPostfix(char *infix, char *postfix) {
    SeqStack S;
    InitStack(&S);

    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        if (isspace(c)) {
            continue;
        }

        if (IsOperand(c)) {
            postfix[j++] = c;
            postfix[j++] = ' ';
        } else if (c == '(') {
            Push(&S, (int)c);
        } else if (c == ')') {
            while (!StackEmpty(S)) {
                int top;
                GetTop(S, &top);

                if ((char)top == '(') {
                    int temp;
                    Pop(&S, &temp);
                    break;
                }

                Pop(&S, &top);
                postfix[j++] = (char)top;
                postfix[j++] = ' ';
            }
        } else if (IsOperator(c)) {
            while (!StackEmpty(S)) {
                int top;
                GetTop(S, &top);

                if ((char)top == '(' || GetPriority((char)top) < GetPriority(c)) {
                    break;
                }

                Pop(&S, &top);
                postfix[j++] = (char)top;
                postfix[j++] = ' ';
            }
            Push(&S, (int)c);
        }
    }

    while (!StackEmpty(S)) {
        int top;
        Pop(&S, &top);
        if ((char)top != '(') {
            postfix[j++] = (char)top;
            postfix[j++] = ' ';
        }
    }

    postfix[j] = '\0';
    return 1;
}

/**
 * Evaluate a postfix expression.
 * @param postfix The postfix expression string
 * @return The computed result
 */
int EvaluatePostfix(char *postfix) {
    SeqStack S;
    InitStack(&S);

    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isspace(postfix[i])) {
            continue;
        }

        if (isdigit(postfix[i])) {
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            i--;
            Push(&S, num);
        } else if (IsOperator(postfix[i])) {
            int b, a, result;
            Pop(&S, &b);
            Pop(&S, &a);

            switch (postfix[i]) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
                case '^':
                    result = 1;
                    for (int k = 0; k < b; k++) {
                        result *= a;
                    }
                    break;
            }
            Push(&S, result);
        }
    }

    int final_result;
    Pop(&S, &final_result);
    return final_result;
}

/* ==================== Recursion Simulation ==================== */

/**
 * Calculate factorial using stack instead of recursion.
 * @param n The non-negative integer
 * @return The factorial result (n!)
 */
int FactorialWithStack(int n) {
    if (n == 0) {
        return 1;
    }

    SeqStack S;
    InitStack(&S);

    int current_n = n;
    int result = 1;

    Push(&S, n);

    while (!StackEmpty(S)) {
        int top;
        Pop(&S, &top);

        if (top == 1 || top == 0) {
            result *= 1;
        } else {
            result *= top;
            Push(&S, top - 1);
        }
    }

    return result;
}

/**
 * Calculate Fibonacci number using stack instead of recursion.
 * @param n The index (non-negative)
 * @return The nth Fibonacci number
 */
int FibonacciWithStack(int n) {
    if (n <= 1) {
        return n;
    }

    int fib[n + 1];
    fib[0] = 0;
    fib[1] = 1;

    SeqStack S;
    InitStack(&S);

    Push(&S, 2);

    while (!StackEmpty(S)) {
        int top;
        Pop(&S, &top);

        if (top <= n) {
            fib[top] = fib[top - 1] + fib[top - 2];
            if (top < n) {
                Push(&S, top + 1);
            }
        }
    }

    return fib[n];
}

/**
 * Solve Tower of Hanoi problem (with stack for simulation).
 * @param n Number of disks
 * @param from Source peg
 * @param aux Auxiliary peg
 * @param to Destination peg
 */
void HanoiWithStack(int n, char from, char aux, char to) {
    printf("Move disk %d from %c to %c\n", n, from, to);
    if (n > 1) {
        HanoiWithStack(n - 1, from, to, aux);
        HanoiWithStack(n - 1, aux, from, to);
    }
}
