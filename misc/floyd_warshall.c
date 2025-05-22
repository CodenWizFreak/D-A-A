#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX 26
#define INF 99999

int nodeCount = 0;
char nodes[MAX]; // Maps index to node name

// Get index of node name, add if not exists
int getNodeIndex(char c) {
    for (int i = 0; i < nodeCount; i++) {
        if (nodes[i] == c)
            return i;
    }
    nodes[nodeCount] = c;
    return nodeCount++;
}

void printSolution(int dist[MAX][MAX]) {
    printf("Shortest distances between every pair of vertices:\n\n   ");
    for (int i = 0; i < nodeCount; i++)
        printf(" %c ", nodes[i]);
    printf("\n");

    for (int i = 0; i < nodeCount; i++) {
        printf(" %c ", nodes[i]);
        for (int j = 0; j < nodeCount; j++) {
            if (dist[i][j] == INF)
                printf(" ∞ ");
            else
                printf("%2d ", dist[i][j]);
        }
        printf("\n");
    }
}

void floydWarshall(int dist[MAX][MAX]) {
    for (int k = 0; k < nodeCount; k++)
        for (int i = 0; i < nodeCount; i++)
            for (int j = 0; j < nodeCount; j++)
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}

int main() {
    int dist[MAX][MAX];
    char u, v;
    int w;
    FILE *file = fopen("fdf.txt", "r");

    if (!file) {
        printf("Failed to open fdf.txt\n");
        return 1;
    }
     int edges;
    fscanf(file, "%d", &edges);

    // Initialize distance matrix
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            dist[i][j] = (i == j) ? 0 : INF;

    // Read edges from file
    for (int i = 0; i < edges; i++) {
        fscanf(file, " %c %c %d", &u, &v, &w);
        int from = getNodeIndex(u);
        int to = getNodeIndex(v);
        dist[from][to] = w;
    }
