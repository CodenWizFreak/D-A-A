#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXV 100          /* max distinct vertex labels */
#define MAXNAME 32

/* ---------- vertex/edge structures ---------- */
typedef struct Edge {
    int to;
    int w;
    struct Edge *next;
} Edge;

typedef struct {
    char name[MAXNAME];
    Edge *adj;
} Vertex;

/* ---------- min-heap for (key,vertex) pairs ---------- */
typedef struct {
    int v;
    int key;
} HeapNode;

typedef struct {
    HeapNode *a;
    int size, cap;
} MinHeap;

MinHeap *newHeap(int cap) {
    MinHeap *h = malloc(sizeof(MinHeap));
    h->a = malloc(cap * sizeof(HeapNode));
    h->size = 0; h->cap = cap;
    return h;
}
void swap(HeapNode *x, HeapNode *y){ HeapNode t=*x;*x=*y;*y=t; }
