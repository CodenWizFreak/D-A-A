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

int main() {
    int edgeCount;
    char u[3], v[3];

    for (int i = 0; i < MAX; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    printf("Enter number of edges: ");
    scanf("%d", &edgeCount);

    printf("Enter %d edges (like a b):\n", edgeCount);
    for (int i = 0; i < edgeCount; i++) {
        scanf("%s %s", u, v);
        int uIdx = findVertexIndex(u);
        int vIdx = findVertexIndex(v);
        unionSet(uIdx, vIdx);
    }

    printf("\nConnected components:\n");
    for (int i = 0; i < vertexCount; i++) {
        printf("Vertex %s belongs to component %d\n", vertices[i], find(i));
    }

    return 0;
}
