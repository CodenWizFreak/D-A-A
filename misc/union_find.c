/*
Enter number of edges: 12
Enter 12 edges (like a b):
a b
a i
i j
b j
c d
c e
c g
e g
d f
d h
f h
e f

Connected components:
Vertex a belongs to component 0
Vertex b belongs to component 0
Vertex i belongs to component 0
Vertex j belongs to component 0
Vertex c belongs to component 1
Vertex d belongs to component 1
Vertex e belongs to component 1
Vertex g belongs to component 1
Vertex f belongs to component 1
Vertex h belongs to component 1

    a ----------------- b
    |                   |
    |   c --------- d   |
    |   | \       / |   |
    |   |  e --- f  |   |
    |   | /       \ |   |
    |   g --------- h   |
    |                   |
    i ----------------- j

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int parent[MAX], rank[MAX];
char vertices[MAX][3];
int vertexCount = 0;

// Maps a vertex name to an index, or creates it if not found
int findVertexIndex(char* v) {
    for (int i = 0; i < vertexCount; i++) {
        if (strcmp(vertices[i], v) == 0)
            return i;
    }
    strcpy(vertices[vertexCount], v);
    return vertexCount++;
}

// Find operation with path compression
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

// Union by rank
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

    // Map root IDs to compact component numbers
    int componentMap[MAX];
    for (int i = 0; i < MAX; i++) {
        componentMap[i] = -1;
    }

    int compCount = 0;
    for (int i = 0; i < vertexCount; i++) {
        int root = find(i);
        if (componentMap[root] == -1) {
            componentMap[root] = compCount++;
        }
    }

    printf("\nConnected components:\n");
    for (int i = 0; i < vertexCount; i++) {
        int root = find(i);
        printf("Vertex %s belongs to component %d\n", vertices[i], componentMap[root]);
    }

    return 0;
}
