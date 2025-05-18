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

void siftUp(MinHeap *h,int i){
    while(i && h->a[i].key < h->a[(i-1)/2].key){
        swap(&h->a[i],&h->a[(i-1)/2]); i=(i-1)/2;
    }
}
void siftDown(MinHeap *h,int i){
    while(1){
        int l=i*2+1, r=i*2+2, s=i;
        if(l<h->size && h->a[l].key < h->a[s].key) s=l;
        if(r<h->size && h->a[r].key < h->a[s].key) s=r;
        if(s==i) break;
        swap(&h->a[i],&h->a[s]); i=s;
    }
}

void heapPush(MinHeap *h,int v,int key){
    if(h->size==h->cap){ h->cap*=2; h->a=realloc(h->a,h->cap*sizeof(HeapNode)); }
    h->a[h->size]=(HeapNode){v,key};
    siftUp(h,h->size++);
}
HeapNode heapPop(MinHeap *h){
    HeapNode root=h->a[0];
    h->a[0]=h->a[--h->size];
    siftDown(h,0);
    return root;
}

int heapEmpty(MinHeap *h){ return h->size==0; }

/* ---------- global graph ---------- */
Vertex g[MAXV];
int V=0, E=0;

int findVertex(const char *name){
    for(int i=0;i<V;i++) if(strcmp(g[i].name,name)==0) return i;
    strcpy(g[V].name,name); g[V].adj=NULL; return V++;
}
void addEdge(int u,int v,int w){
    Edge *e=malloc(sizeof(Edge)); e->to=v; e->w=w; e->next=g[u].adj; g[u].adj=e;
}
