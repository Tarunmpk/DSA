#include <stdio.h>
#include <stdlib.h>

// Define a stack structure
struct Stack {
    int data;
    struct Stack* next;
};

// Function to create a new stack node
struct Stack* createStackNode(int data) {
    struct Stack* newNode = (struct Stack*)malloc(sizeof(struct Stack));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to check if the stack is empty
int isStackEmpty(struct Stack* top) {
    return top == NULL;
}

// Function to push an element onto the stack
void push(struct Stack** top, int data) {
    struct Stack* newNode = createStackNode(data);
    newNode->next = *top;
    *top = newNode;
}

// Function to pop an element from the stack
int pop(struct Stack** top) {
    if (isStackEmpty(*top)) {
        printf("Stack underflow\n");
        return -1;
    }
    struct Stack* temp = *top;
    int popped = temp->data;
    *top = (*top)->next;
    free(temp);
    return popped;
}

// Function to compute factorial using stack
int factorial(int n) {
    struct Stack* stack = NULL;
    int result = 1;

    // Push all integers from 1 to n onto the stack
    for (int i = 1; i <= n; i++) {
        push(&stack, i);
    }

    // Pop all elements and multiply them
    while (!isStackEmpty(stack)) {
        result *= pop(&stack);
    }

    return result;
}

// Function to print Fibonacci series using stack
void printFibonacciUsingStack(int n) {
    if (n <= 0) {
        printf("Invalid Number of terms\n");
        return;
    }

    // Initialize the stack
    struct Stack* stack = NULL;

    // Special case for the first Fibonacci number
    if (n >= 1) {
        printf("0 ");
        push(&stack, 0); // fib(0)
    }
    if (n >= 2) {
        printf("1 ");
        push(&stack, 1); // fib(1)
    }

    // Generate the Fibonacci series using the stack
    for (int i = 3; i <= n; i++) {
        int prev1 = pop(&stack); // fib(i-1)
        int prev2 = pop(&stack); // fib(i-2)
        int next = prev1 + prev2; // fib(i)

        printf("%d ", next);

        // Push the previous and next Fibonacci numbers back onto the stack
        push(&stack, prev1);  // Maintain the previous number on stack for future use
        push(&stack, next);   // Push the current Fibonacci number
    }

    // Clean up the stack
    while (!isStackEmpty(stack)) {
        pop(&stack);
    }

    printf("\n");
}

// Menu-driven program
int main() {
    int choice;
    int number;

    do {
        printf("\nMenu:\n");
        printf("1. Factorial of a given number\n");
        printf("2. Generate Fibonacci series\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a number to find its factorial: ");
                scanf("%d", &number);
                if (number < 0) {
                    printf("Factorial is not defined for negative numbers.\n");
                } else {
                    printf("Factorial of %d is %d\n", number, factorial(number));
                }
                break;
            case 2:
                printf("Enter the number of terms in Fibonacci series: ");
                scanf("%d", &number);
                printf("Fibonacci series up to %d terms:\n", number);
                printFibonacciUsingStack(number);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}

