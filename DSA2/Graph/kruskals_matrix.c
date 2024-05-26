#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct Edge {
    int src, dest, weight;
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

int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}


void Union(int parent[], int x, int y) {
    parent[x] = y;
}

int myComp(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

void KruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V];
    int e = 0;
    int i = 0;

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

    int* parent = (int*)malloc(V * sizeof(int));
    memset(parent, -1, sizeof(int) * V);

    while (e < V - 1 && i < graph->E) {
        struct Edge next_edge = graph->edge[i++];
        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            Union(parent, x, y);
        }
    }

    printf("\nMinimum Spanning Tree using Kruskal's algorithm:\n");
    int minimumCost = 0;
    for (i = 0; i < e; ++i) {
        printf("%d - %d : %d\n", result[i].src, result[i].dest, result[i].weight);
        minimumCost += result[i].weight;
    }
    printf("Total Weight of MST: %d\n", minimumCost);

    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            int found = 0;
            for (int k = 0; k < e; ++k) {
                if ((result[k].src == i && result[k].dest == j) || (result[k].src == j && result[k].dest == i)) {
                    printf("%d\t", result[k].weight);
                    found = 1;
                    break;
                }
            }
            if (found == 0)
                printf("0\t");
        }
        printf("\n");
    }

    free(parent);
}

int main() {
    int V, E;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    struct Graph* graph = createGraph(V, E);

    printf("Enter edges and their weights (src dest weight):\n");
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        graph->edge[i].src = src;
        graph->edge[i].dest = dest;
        graph->edge[i].weight = weight;
    }

    KruskalMST(graph);

    return 0;
}
