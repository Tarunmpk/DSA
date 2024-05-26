// WAP to convert a given Infix expression into its equivalent Postfix expression and evaluate it using stack.
//infix to postfix using stack
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

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

// Function to convert infix expression to postfix expression
void infixToPostfix(char s[], char result[]) {
    int resultIndex = 0;
    int len = strlen(s);
    char stack[1000];
    int stackIndex = -1;

    for (int i = 0; i < len; i++) {
        char c = s[i];

        // If the scanned character is an operand, add it to the output string.
        if (isalnum(c)) {
            result[resultIndex++] = c;
        }
        // If the scanned character is an ‘(‘, push it to the stack.
        else if (c == '(') {
            stack[++stackIndex] = c;
        }
        // If the scanned character is an ‘)’, pop and add to the output string from the stack
        // until an ‘(‘ is encountered.
        else if (c == ')') {
            while (stackIndex >= 0 && stack[stackIndex] != '(') {
                result[resultIndex++] = stack[stackIndex--];
            }
            stackIndex--; // Pop '('
        }
        // If an operator is scanned
        else {
            while (stackIndex >= 0 && (prec(s[i]) < prec(stack[stackIndex]) ||
                                       (prec(s[i]) == prec(stack[stackIndex]) &&
                                        associativity(s[i]) == 'L'))) {
                result[resultIndex++] = stack[stackIndex--];
            }
            stack[++stackIndex] = c;
        }
    }

    // Pop all the remaining elements from the stack
    while (stackIndex >= 0) {
        result[resultIndex++] = stack[stackIndex--];
    }

    result[resultIndex] = '\0';
}

// Function to evaluate postfix expression
int evaluatePostfix(char postfix[]) {
    int len = strlen(postfix);
    int stack[1000];
    int top = -1;

    for (int i = 0; i < len; i++) {
        char c = postfix[i];
        if (isdigit(c)) {
            stack[++top] = c - '0'; // Convert char to int
        } else {
            int operand2 = stack[top--];
            int operand1 = stack[top--];
            switch (c) {
                case '+':
                    stack[++top] = operand1 + operand2;
                    break;
                case '-':
                    stack[++top] = operand1 - operand2;
                    break;
                case '*':
                    stack[++top] = operand1 * operand2;
                    break;
                case '/':
                    stack[++top] = operand1 / operand2;
                    break;
                case '^':
                    stack[++top] = (int)pow(operand1, operand2);
                    break;
            }
        }
    }
    return stack[top];
}

int main() {
    char infix[1000];
    char postfix[1000];

    // Taking input from the user
    printf("Enter an infix expression: ");
    scanf("%s", infix);

    // Convert infix to postfix
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    // Evaluate postfix expression
    int result = evaluatePostfix(postfix);
    printf("Result: %d\n", result);

    return 0;
}


