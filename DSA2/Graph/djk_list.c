#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct node {
    int vertex;
    int weight;
    struct node* next;
};

struct node* A[MAX_VERTICES];
int n, e;

int vertex(int dist[], int visited[]) {
    int min = 999, a;
    for (int i = 0; i < n; i++) {
        if (dist[i] < min && visited[i] == 0) {
            min = dist[i];
            a = i;
        }
    }
    return a;
}

void display(int dist[]) {
    printf("\nVertex \t Distance from Source:\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\n", i, dist[i]);
}

void dijkstra(struct node* A[]) {
    int s;
    printf("\nEnter starting vertex: ");
    scanf("%d", &s);
    int dist[MAX_VERTICES], visited[MAX_VERTICES];
    for (int i = 0; i < n; i++) {
        dist[i] = 999;
        visited[i] = 0;
    }
    dist[s] = 0;

    for (int i = 0; i < n; i++) {
        int u = vertex(dist, visited);
        visited[u] = 1;
        struct node* current = A[u];
        while (current != NULL) {
            if (!visited[current->vertex] && dist[u] != 999 && dist[u] + current->weight < dist[current->vertex])
                dist[current->vertex] = dist[u] + current->weight;
            current = current->next;
        }
    }
    display(dist);
}

void list() {
    int u, v, w;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        A[i] = NULL;
    }

    printf("Enter the number of edges: ");
    scanf("%d", &e);

    struct node* new;
    for (int i = 0; i < e; i++) {
        printf("\nEnter edge (u v): ");
        scanf("%d %d", &u, &v);
        printf("\nEnter weight from edge %d to %d: ", u, v);
        scanf("%d", &w);

        new = (struct node*)malloc(sizeof(struct node));
        new->vertex = v;
        new->weight = w;
        new->next = A[u];
        A[u] = new;

        new = (struct node*)malloc(sizeof(struct node));
        new->vertex = u;
        new->weight = w;
        new->next = A[v];
        A[v] = new;
    }

    // Display the adjacency list
    printf("\nAdjacency List:\n");
    for (int i = 0; i < n; i++) {
        struct node* current = A[i];
        printf("Vertex %d: ", i);
        while (current != NULL) {
            printf("(%d, %d) ", current->vertex, current->weight);
            current = current->next;
        }
        printf("\n");
    }
}

int main() {
    list();
    dijkstra(A);
    return 0;
}

