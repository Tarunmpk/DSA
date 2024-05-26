#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int **createGraph(int V, int E);
void printGraph(int **graph, int V);
void primMST(int **graph, int V);
int minKey(int key[], int mstSet[], int V);
void printMST(int parent[], int V, int **graph);

int main() {
    int V, E;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    int **graph = createGraph(V, E);

    printf("Enter each edge (vertex1 vertex2 weight), indices start from 0:\n");
    for (int i = 0; i < E; i++) {
        int v1, v2, weight;
        scanf("%d %d %d", &v1, &v2, &weight);
        graph[v1][v2] = weight;
        graph[v2][v1] = weight; // Since the graph is undirected
    }

    printf("The adjacency matrix is:\n");
    printGraph(graph, V);

    primMST(graph, V);

    // Freeing the dynamically allocated memory
    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}

int **createGraph(int V, int E) {
    int **graph = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        graph[i] = (int *)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0; // Initialize the graph with 0s
        }
    }
    return graph;
}

void printGraph(int **graph, int V) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }
}

void primMST(int **graph, int V) {
    int parent[V]; 
    int key[V];   
    int mstSet[V]; 

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX, mstSet[i] = 0;
    }

    key[0] = 0;     
    parent[0] = -1; 

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);

        mstSet[u] = 1;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u, key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, V, graph);
}

int minKey(int key[], int mstSet[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v], min_index = v;
        }
    }

    return min_index;
}

void printMST(int parent[], int V, int **graph) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
    }
}

