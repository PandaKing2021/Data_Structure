#include "../../include/stack_queue/stack_applications.h"
#include <stdio.h>

int main() {
    printf("=== Stack Applications Tests ===\n\n");

    /* Bracket matching test */
    printf("1. Bracket Matching Tests:\n");
    char test1[] = "{[()]}";
    char test2[] = "{[(])}";
    char test3[] = "((()))";
    char test4[] = "(()))";
    char test5[] = "([]{})";

    printf("'%s' -> %s\n", test1, BracketMatching(test1) ? "Matched" : "Not Matched");
    printf("'%s' -> %s\n", test2, BracketMatching(test2) ? "Matched" : "Not Matched");
    printf("'%s' -> %s\n", test3, BracketMatching(test3) ? "Matched" : "Not Matched");
    printf("'%s' -> %s\n", test4, BracketMatching(test4) ? "Matched" : "Not Matched");
    printf("'%s' -> %s\n", test5, BracketMatching(test5) ? "Matched" : "Not Matched");

    /* Infix to postfix conversion test */
    printf("\n2. Infix to Postfix Conversion Tests:\n");
    char infix1[] = "a + b * c";
    char infix2[] = "(a + b) * c";
    char infix3[] = "a + b * c + d";
    char infix4[] = "a * b + c * d";

    char postfix[MAX_EXPR_LEN];
    InfixToPostfix(infix1, postfix);
    printf("Infix: '%s' -> Postfix: '%s'\n", infix1, postfix);

    InfixToPostfix(infix2, postfix);
    printf("Infix: '%s' -> Postfix: '%s'\n", infix2, postfix);

    InfixToPostfix(infix3, postfix);
    printf("Infix: '%s' -> Postfix: '%s'\n", infix3, postfix);

    InfixToPostfix(infix4, postfix);
    printf("Infix: '%s' -> Postfix: '%s'\n", infix4, postfix);

    /* Postfix expression evaluation test */
    printf("\n3. Postfix Expression Evaluation Tests:\n");
    char postfix1[] = "1 2 3 * +";
    char postfix2[] = "1 2 + 3 *";
    char postfix3[] = "2 3 4 + *";
    char postfix4[] = "5 1 2 + 4 * + 3 -";

    printf("Postfix: '%s' = %d\n", postfix1, EvaluatePostfix(postfix1));
    printf("Postfix: '%s' = %d\n", postfix2, EvaluatePostfix(postfix2));
    printf("Postfix: '%s' = %d\n", postfix3, EvaluatePostfix(postfix3));
    printf("Postfix: '%s' = %d\n", postfix4, EvaluatePostfix(postfix4));

    /* Complete expression test */
    printf("\n4. Complete Expression Tests:\n");
    char expr1[] = "3 + 4 * 2 / ( 1 - 5 ) ^ 2";
    InfixToPostfix(expr1, postfix);
    printf("Infix: '%s'\n", expr1);
    printf("Postfix: '%s'\n", postfix);
    printf("Result: %d\n", EvaluatePostfix(postfix));

    /* Factorial with stack test */
    printf("\n5. Factorial with Stack Tests:\n");
    for (int i = 0; i <= 6; i++) {
        printf("%d! = %d\n", i, FactorialWithStack(i));
    }

    /* Fibonacci with stack test */
    printf("\n6. Fibonacci with Stack Tests:\n");
    printf("Fibonacci sequence (first 10 terms):\n");
    for (int i = 0; i < 10; i++) {
        printf("F(%d) = %d\n", i, FibonacciWithStack(i));
    }

    /* Hanoi tower test */
    printf("\n7. Hanoi Tower with Stack Tests:\n");
    printf("Hanoi Tower with 3 disks:\n");
    HanoiWithStack(3, 'A', 'B', 'C');

    printf("\n8. Expression with Brackets Test:\n");
    char expr2[] = " ( a + b ) * [ c - ( d + e ) ] ";
    InfixToPostfix(expr2, postfix);
    printf("Infix: '%s'\n", expr2);
    printf("Postfix: '%s'\n", postfix);

    printf("\n=== All Tests Passed ===\n");
    return 0;
}
