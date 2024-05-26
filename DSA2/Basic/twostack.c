#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int arr[MAX_SIZE];
int top1 = -1;       // Top index of the first stack
int top2 = MAX_SIZE; // Top index of the second stack

// Function to push an element to the first stack
void push1(int value) {
    if (top1 < top2 - 1) {
        arr[++top1] = value;
        printf("Pushed %d to stack 1\n", value);
    } else {
        printf("Stack Overflow in stack1 by element: %d\n", value);
    }
}

// Function to push an element to the second stack
void push2(int value) {
    if (top1 < top2 - 1) {
        arr[--top2] = value;
        printf("Pushed %d to stack 2\n", value);
    } else {
        printf("Stack Overflow in stack2 by element: %d\n", value);
    }
}

// Function to pop an element from the first stack
int pop1() {
    if (top1 >= 0) {
        int value = arr[top1--];
        printf("Popped %d from stack 1\n", value);
        return value;
    } else {
        printf("Stack UnderFlow in stack1\n");
        return -1;
    }
}

// Function to pop an element from the second stack
int pop2() {
    if (top2 < MAX_SIZE) {
        int value = arr[top2++];
        printf("Popped %d from stack 2\n", value);
        return value;
    } else {
        printf("Stack UnderFlow in stack2\n");
        return -1;
    }
}

// Function to check if both stacks are full
int isStackFull() {
    return top1 >= top2 - 1;
}

// Function to check if the first stack is empty
int isStack1Empty() {
    return top1 == -1;
}

// Function to check if the second stack is empty
int isStack2Empty() {
    return top2 == MAX_SIZE;
}

// Function to display the first stack
void displayStack1() {
    if (isStack1Empty()) {
        printf("Stack 1 is empty\n");
    } else {
        printf("Stack 1: ");
        for (int i = 0; i <= top1; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}

// Function to display the second stack
void displayStack2() {
    if (isStack2Empty()) {
        printf("Stack 2 is empty\n");
    } else {
        printf("Stack 2: ");
        for (int i = MAX_SIZE - 1; i >= top2; i--) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}

int main() {
    int choice, stackNumber, value;

    while (1) {
        printf("\n1. Push\n2. Pop\n3. Check if Stacks are Full\n4. Check if Stack is Empty\n5. Display Stack\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter stack number (1 or 2): ");
                scanf("%d", &stackNumber);
                printf("Enter value to push: ");
                scanf("%d", &value);
                if (stackNumber == 1) {
                    push1(value);
                } else if (stackNumber == 2) {
                    push2(value);
                } else {
                    printf("Invalid stack number\n");
                }
                break;
            case 2:
                printf("Enter stack number (1 or 2): ");
                scanf("%d", &stackNumber);
                if (stackNumber == 1) {
                    int poppedValue = pop1();
                    if (poppedValue != -1) {
                        printf("Popped element from stack1: %d\n", poppedValue);
                    }
                } else if (stackNumber == 2) {
                    int poppedValue = pop2();
                    if (poppedValue != -1) {
                        printf("Popped element from stack2: %d\n", poppedValue);
                    }
                } else {
                    printf("Invalid stack number\n");
                }
                break;
            case 3:
                if (isStackFull()) {
                    printf("Both stacks are full\n");
                } else {
                    printf("Stacks are not full\n");
                }
                break;
            case 4:
                printf("Enter stack number (1 or 2): ");
                scanf("%d", &stackNumber);
                if (stackNumber == 1) {
                    if (isStack1Empty()) {
                        printf("Stack 1 is empty\n");
                    } else {
                        printf("Stack 1 is not empty\n");
                    }
                } else if (stackNumber == 2) {
                    if (isStack2Empty()) {
                        printf("Stack 2 is empty\n");
                    } else {
                        printf("Stack 2 is not empty\n");
                    }
                } else {
                    printf("Invalid stack number\n");
                }
                break;
            case 5:
                printf("Enter stack number (1 or 2): ");
                scanf("%d", &stackNumber);
                if (stackNumber == 1) {
                    displayStack1();
                } else if (stackNumber == 2) {
                    displayStack2();
                } else {
                    printf("Invalid stack number\n");
                }
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice, please try again\n");
        }
    }

    return 0;
}

