#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Edge {
    int src, dest, weight;
};

struct Subset {
    int parent;
    int rank;
};

struct Graph {
    int V, E;
    struct Edge* edge;
};

struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int myComp(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

// Function to construct MST using Kruskal's algorithm
void KruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V];  // Tnis will store the resultant MST
    int e = 0;  // Index variable, used for result[]

    int i = 0;  // Index variable, used for sorted edges

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));

    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < graph->E) {
        struct Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Print the MST
    printf("Minimum Spanning Tree using Kruskal's algorithm:\n");
    for (i = 0; i < e; ++i)
        printf("%d - %d : %d\n", result[i].src, result[i].dest, result[i].weight);

    free(subsets);
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest, int weight, int* edgeIndex) {
    graph->edge[*edgeIndex].src = src;
    graph->edge[*edgeIndex].dest = dest;
    graph->edge[*edgeIndex].weight = weight;
    (*edgeIndex)++;
}

// Function to print the adjacency list representation of graph
void printAdjList(struct Graph* graph) {
    printf("Adjacency List:\n");
    for (int i = 0; i < graph->V; i++) {
        printf("Vertex %d: ", i);
        for (int j = 0; j < graph->E; j++) {
            if (graph->edge[j].src == i)
                printf("(%d, %d) ", graph->edge[j].dest, graph->edge[j].weight);
            else if (graph->edge[j].dest == i)
                printf("(%d, %d) ", graph->edge[j].src, graph->edge[j].weight);
        }
        printf("\n");
    }
}

int main() {
    int V, E;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    struct Graph* graph = createGraph(V, E);

    printf("Enter edges and their weights (src dest weight):\n");
    int edgeIndex = 0;
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight, &edgeIndex);
    }

    printAdjList(graph);

    KruskalMST(graph);

    free(graph->edge);
    free(graph);

    return 0;
}

