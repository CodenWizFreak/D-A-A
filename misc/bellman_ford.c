/*

Enter source vertex (a-f): c
Vertex   Distance from source 'c'
  a          INF
  b          -4
  c          0
  d          14
  e          14
  f          10

*/
    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_VERTICES 26   // support up to 'z'
#define INF INT_MAX

typedef struct {
    int from, to, weight;
} Edge;

int vertexIndex(char c) {
    return c - 'a';
}

char vertexChar(int i) {
    return 'a' + i;
}

void bellmanFord(Edge edges[], int E, int V, int src, int dist[]) {
    // Initialize distances
    for (int i = 0; i < V; i++)
        dist[i] = INF;
    dist[src] = 0;

    // Relax edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].from;
            int v = edges[j].to;
            int w = edges[j].weight;
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    // Check for negative-weight cycle
    for (int j = 0; j < E; j++) {
        int u = edges[j].from;
        int v = edges[j].to;
        int w = edges[j].weight;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            printf("Graph contains a negative weight cycle\n");
            return;
        }
    }

    // Print distances
    printf("Vertex   Distance from source '%c'\n", vertexChar(src));
    for (int i = 0; i < V; i++) {
        printf("  %c \t\t", vertexChar(i));
        if (dist[i] == INF)
            printf("INF\n");
        else
            printf("%d\n", dist[i]);
    }
}

int main() {
    FILE *fp = fopen("bmf.txt", "r");
    if (!fp) {
        perror("Unable to open file");
        return 1;
    }

    int V;
    fscanf(fp, "%d", &V);

    Edge edges[1000];
    int E = 0;
    char from, to;
    int weight;

    while (fscanf(fp, " %c %c %d", &from, &to, &weight) == 3) {
        edges[E].from = vertexIndex(from);
        edges[E].to = vertexIndex(to);
        edges[E].weight = weight;
        E++;
    }
    fclose(fp);

    int dist[MAX_VERTICES];
    char src_char;
    printf("Enter source vertex (a-%c): ", 'a' + V - 1);
    scanf(" %c", &src_char);

    int src = vertexIndex(src_char);
    if (src < 0 || src >= V) {
        printf("Invalid source vertex.\n");
        return 1;
    }

    bellmanFord(edges, E, V, src, dist);

    return 0;
}
