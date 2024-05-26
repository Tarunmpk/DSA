//djikstras using adjacency matrix
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

int G[MAX_VERTICES][MAX_VERTICES];
int n;

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

void dijkstra(int G[][MAX_VERTICES]) {
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
        for (int j = 0; j < n; j++) {
            if (!visited[j] && G[u][j] && dist[u] != 999 && dist[u] + G[u][j] < dist[j])
                dist[j] = dist[u] + G[u][j];
        }
    }
    display(dist);
}

void matrix() {
    int e, a, b, w;
    printf("\nEnter the number of vertices: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            G[i][j] = 999;
        }
    }

    printf("\nEnter the number of edges: ");
    scanf("%d", &e);

    for (int i = 0; i < e; i++) {
        printf("\nEnter edge (u v): ");
        scanf("%d %d", &a, &b);
        printf("\nEnter weight from edge %d to %d: ", a, b);
        scanf("%d", &w);
        G[a][b] = G[b][a] = w;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5d ", G[i][j]);
        }
        printf("\n");
    }
}

int main() {
    matrix();
    dijkstra(G);
    return 0;
}




