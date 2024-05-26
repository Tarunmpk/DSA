#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Structure to represent the adjacency list
struct Graph {
    int numVertices;
    struct Node** adjLists;
};

// Function to create a new node
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with given number of vertices
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    // Allocate memory for adjacency lists
    graph->adjLists = (struct Node**)malloc(vertices * sizeof(struct Node*));

    // Initialize each adjacency list as empty
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src (for undirected graph)
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Function to display the adjacency list
void displayAdjList(struct Graph* graph) {
    printf("Adjacency List:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        struct Node* temp = graph->adjLists[i];
        printf("Vertex %d: ", i);
        while (temp != NULL) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Structure to represent a stack node for DFS traversal
struct StackNode {
    int vertex;
    struct StackNode* next;
};

// Function to create a new stack node
struct StackNode* createStackNode(int v) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to push a vertex onto the stack
void push(struct StackNode** top, int v) {
    struct StackNode* newNode = createStackNode(v);
    newNode->next = *top;
    *top = newNode;
}

// Function to pop a vertex from the stack
int pop(struct StackNode** top) {
    if (*top == NULL) {
        printf("Stack underflow.\n");
        return -1;
    }
    int vertex = (*top)->vertex;
    struct StackNode* temp = *top;
    *top = (*top)->next;
    free(temp);
    return vertex;
}

// Function to perform Depth-First Search (DFS) traversal
void DFS(struct Graph* graph, int startVertex) {
    int* visited = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = 0;
    }

    // Create an empty stack for DFS traversal
    struct StackNode* stack = NULL;

    // Push the start vertex onto the stack
    push(&stack, startVertex);

    printf("Depth First Search Traversal: ");

    while (stack != NULL) {
        // Pop a vertex from the stack
        int currentVertex = pop(&stack);

        // If the vertex is not visited yet, mark it as visited and process it
        if (!visited[currentVertex]) {
            printf("%d ", currentVertex);
            visited[currentVertex] = 1;

            // Visit all adjacent vertices of the popped vertex and push them onto the stack
            struct Node* temp = graph->adjLists[currentVertex];
            while (temp != NULL) {
                if (!visited[temp->vertex]) {
                    push(&stack, temp->vertex);
                }
                temp = temp->next;
            }
        }
    }
    printf("\n");

    free(visited);
}

int main() {
    int vertices, edges, i, src, dest;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    // Create a graph with given number of vertices
    struct Graph* graph = createGraph(vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    // Input edges
    printf("Enter edges (format: from to):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    // Display adjacency list
    displayAdjList(graph);

    // Choose starting vertex for DFS
    int startVertex;
    printf("\nEnter the starting vertex for DFS: ");
    scanf("%d", &startVertex);

    // Perform DFS traversal
    DFS(graph, startVertex);

    return 0;
}


