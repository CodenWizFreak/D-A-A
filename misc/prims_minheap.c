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

MinHeap *heapCreate(int n,int *key){
    MinHeap *mh=malloc(sizeof(MinHeap));
    mh->pos=malloc(n*sizeof(int));
    mh->h  =malloc(n*sizeof(int));
    mh->key=key;
    mh->size=0; mh->cap=n;
    for(int i=0;i<n;i++) mh->pos[i]=-1;
    return mh;
}
