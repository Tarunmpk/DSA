#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure to represent a node in the stack
struct StackNode {
    int data;
    struct StackNode* next;
};

// Structure to represent the stack
struct Stack {
    struct StackNode* top;
};

// Function to create a new stack node
struct StackNode* createStackNode(int data) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create an empty stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

// Function to push a data onto the stack
void push(struct Stack* stack, int data) {
    struct StackNode* newNode = createStackNode(data);
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop a data from the stack
int pop(struct Stack* stack) {
    if (stack->top == NULL) {
        printf("Stack underflow.\n");
        return -1;
    }
    int data = stack->top->data;
    struct StackNode* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    return data;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

// Function to display the adjacency matrix
void displayAdjMatrix(int adjMatrix[MAX][MAX], int vertices) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Function to perform Depth-First Search (DFS) traversal
void DFS(int adjMatrix[MAX][MAX], int visited[MAX], int start, int vertices) {
    struct Stack* stack = createStack();
    int i, current;

    push(stack, start);
    visited[start] = 1;

    printf("%d ", start);

    while (!isEmpty(stack)) {
        current = pop(stack);

        for (i = 0; i < vertices; i++) {
            if (adjMatrix[current][i] && !visited[i]) {
                push(stack, i);
                visited[i] = 1;
                printf("%d ", i);
            }
        }
    }
}

int main() {
    int adjMatrix[MAX][MAX], visited[MAX], vertices, edges, i, j, v;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    // Initialize adjacency matrix and visited array
    for (i = 0; i < vertices; i++) {
        visited[i] = 0;
        for (j = 0; j < vertices; j++) {
            adjMatrix[i][j] = 0;
        }
    }

    // Input edges
    printf("Enter edges (format: from to):\n");
    for (i = 0; i < edges; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        adjMatrix[from][to] = 1;
        adjMatrix[to][from] = 1; // For undirected graph
    }

    // Display adjacency matrix
    displayAdjMatrix(adjMatrix, vertices);

    // Choose starting vertex for DFS
    printf("\nEnter the starting vertex for DFS: ");
    scanf("%d", &v);

    // Perform DFS traversal
    printf("Depth First Search Traversal: ");
    DFS(adjMatrix, visited, v, vertices);

    printf("\n");

    return 0;
}



