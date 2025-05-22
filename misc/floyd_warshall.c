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
