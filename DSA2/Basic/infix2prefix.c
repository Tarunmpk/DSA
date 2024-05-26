#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to return precedence of operators
int prec(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// Function to return associativity of operators
char associativity(char c) {
    if (c == '^')
        return 'R';
    return 'L'; // Default to left-associative
}

// Function to reverse a string
void reverse(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// Function to convert infix expression to prefix expression
void infixToPrefix(char infix[], char prefix[]) {
    int len = strlen(infix);
    char stack[1000];
    int stackIndex = -1;
    int prefixIndex = 0;

    // Reverse the infix expression
    reverse(infix);

    for (int i = 0; i < len; i++) {
        char c = infix[i];

        // If the scanned character is an operand, add it to the output string.
        if (isalnum(c)) {
            prefix[prefixIndex++] = c;
        }
        // If the scanned character is an ‘)’, push it to the stack.
        else if (c == ')') {
            stack[++stackIndex] = c;
        }
        // If the scanned character is an ‘(‘, pop and add to the output string from the stack
        // until an ‘)’ is encountered.
        else if (c == '(') {
            while (stackIndex >= 0 && stack[stackIndex] != ')') {
                prefix[prefixIndex++] = stack[stackIndex--];
            }
            stackIndex--; // Pop ')'
        }
        // If an operator is scanned
        else {
            while (stackIndex >= 0 && (prec(c) < prec(stack[stackIndex]) ||
                                       (prec(c) == prec(stack[stackIndex]) &&
                                        associativity(c) == 'L'))) {
                prefix[prefixIndex++] = stack[stackIndex--];
            }
            stack[++stackIndex] = c;
        }
    }

    // Pop all the remaining elements from the stack
    while (stackIndex >= 0) {
        prefix[prefixIndex++] = stack[stackIndex--];
    }

    prefix[prefixIndex] = '\0';
}

int main() {
    char infix[1000];
    char prefix[1000];

    // Taking input from the user
    printf("Enter an infix expression: ");
    scanf("%s", infix);

    // Convert infix to prefix
    infixToPrefix(infix, prefix);
    reverse(prefix); // Reverse the result to get the final prefix expression
    printf("Prefix expression: %s\n", prefix);

    return 0;
}

