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

void swap(MinHeap *mh,int i,int j){
    int vi=mh->h[i], vj=mh->h[j];
    mh->h[i]=vj; mh->h[j]=vi;
    mh->pos[vi]=j; mh->pos[vj]=i;
}
void siftUp(MinHeap *mh,int i){
    while(i&&mh->key[mh->h[i]]<mh->key[mh->h[(i-1)/2]]){
        swap(mh,i,(i-1)/2); i=(i-1)/2;
    }
}
void siftDown(MinHeap *mh,int i){
    while(1){
        int l=i*2+1,r=i*2+2,s=i;
        if(l<mh->size && mh->key[mh->h[l]]<mh->key[mh->h[s]]) s=l;
        if(r<mh->size && mh->key[mh->h[r]]<mh->key[mh->h[s]]) s=r;
        if(s==i) break;
        swap(mh,i,s); i=s;
    }
}

void heapInsert(MinHeap *mh,int v){
    mh->h[mh->size]=v; mh->pos[v]=mh->size;
    siftUp(mh,mh->size++);
}
int heapExtractMin(MinHeap *mh){
    int v=mh->h[0];
    mh->pos[v]=-1;
    mh->h[0]=mh->h[--mh->size];
    mh->pos[mh->h[0]]=0;
    siftDown(mh,0);
    return v;
}
void heapDecreaseKey(MinHeap *mh,int v,int newKey){
    mh->key[v]=newKey;
    siftUp(mh,mh->pos[v]);
}
int heapEmpty(MinHeap *mh){ return mh->size==0; }
