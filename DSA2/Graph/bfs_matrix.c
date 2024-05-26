#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int queue[MAX];
int front = -1, rear = -1;

void enqueue(int data) {
    if (rear == MAX - 1) {
        printf("Queue is full.\n");
        return;
    }
    if (front == -1)
        front = 0;
    rear++;
    queue[rear] = data;
}

int dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue is empty.\n");
        return -1;
    }
    int data = queue[front];
    front++;
    return data;
}

int isEmpty() {
    if (front == -1 || front > rear)
        return 1;
    else
        return 0;
}

void displayAdjMatrix(int adjMatrix[MAX][MAX], int vertices) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

void BFS(int adjMatrix[MAX][MAX], int visited[MAX], int start, int vertices) {
    int i, current;
    enqueue(start);
    visited[start] = 1;

    printf("Breadth First Search Traversal: ");

    while (!isEmpty()) {
        current = dequeue();
        printf("%d ", current);

        for (i = 0; i < vertices; i++) {
            if (adjMatrix[current][i] && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
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

    // Choose starting vertex for BFS
    printf("\nEnter the starting vertex for BFS: ");
    scanf("%d", &v);

    // Perform BFS traversal
    BFS(adjMatrix, visited, v, vertices);

    printf("\n");

    return 0;
}


