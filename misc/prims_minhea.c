#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXV 100
#define MAXNAME 32

typedef struct Edge { int to,w; struct Edge *next; } Edge;
typedef struct { char name[MAXNAME]; Edge *adj; } Vertex;

/* ---------- Indexed Min-Heap ---------- */
typedef struct {
    int *pos;          /* vertex → heap index (-1 if not in heap) */
    int *key;          /* weights array (external) */
    int *h;            /* heap of vertices */
    int size, cap;
} MinHeap;

