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
