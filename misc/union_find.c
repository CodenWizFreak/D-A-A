#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int parent[MAX], rank[MAX];
char vertices[MAX][3];
int vertexCount = 0;

int findVertexIndex(char* v) {
    for (int i = 0; i < vertexCount; i++) {
        if (strcmp(vertices[i], v) == 0)
            return i;
    }
    strcpy(vertices[vertexCount], v);
    return vertexCount++;
}

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);  // Path compression
    return parent[x];
}

void unionSet(int x, int y) {
    int xroot = find(x);
    int yroot = find(y);

    if (xroot == yroot)
        return;

    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}
