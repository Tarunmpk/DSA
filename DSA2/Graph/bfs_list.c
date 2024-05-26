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

// Function to perform Breadth-First Search (BFS) traversal
void BFS(struct Graph* graph, int startVertex) {
    int* visited = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = 0;
    }

    // Create a queue for BFS
    int queue[graph->numVertices];
    int front = 0, rear = 0;

    // Mark the current node as visited and enqueue it
    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    printf("Breadth First Search Traversal: ");

    while (front < rear) {
        // Dequeue a vertex from queue and print it
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        // Get all adjacent vertices of the dequeued vertex currentVertex.
        // If an adjacent vertex has not been visited, then mark it visited and enqueue it
        struct Node* temp = graph->adjLists[currentVertex];
        while (temp != NULL) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
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

    // Choose starting vertex for BFS
    int startVertex;
    printf("\nEnter the starting vertex for BFS: ");
    scanf("%d", &startVertex);

    // Perform BFS traversal
    BFS(graph, startVertex);

    return 0;
}


