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
