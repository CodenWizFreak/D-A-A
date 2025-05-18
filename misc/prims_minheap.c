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

void loadGraph(const char *file){
    FILE *fp=fopen(file,"r");
    if(!fp){ perror("graph.txt"); exit(1); }
    int declaredV; if(fscanf(fp,"%d",&declaredV)!=1){ fprintf(stderr,"Bad file\n"); exit(1); }
    char s1[MAXNAME], s2[MAXNAME]; int w;
    while(fscanf(fp,"%s %s %d",s1,s2,&w)==3){
        int u=findVertex(s1), v=findVertex(s2);
        addEdge(u,v,w); addEdge(v,u,w);
        ++E;
    }
    fclose(fp);
    if(V!=declaredV)
        fprintf(stderr,"Warning: first line said %d vertices, but %d unique labels found.\n",declaredV,V);
}

/* ---------- Prim’s algorithm (lazy) ---------- */
void prim(int start){
    int inMST[MAXV]={0}, parent[MAXV], cost[MAXV];
    for(int i=0;i<V;i++){ cost[i]=INT_MAX; parent[i]=-1; }
    MinHeap *h=newHeap(E*2+1);
    heapPush(h,start,0); cost[start]=0;

    long long total=0;
    while(!heapEmpty(h)){
        HeapNode n=heapPop(h);
        int u=n.v;
        if(inMST[u]) continue;          /* skip stale duplicates */
        inMST[u]=1; total+=n.key;

        for(Edge *e=g[u].adj;e;e=e->next){
            int v=e->to, w=e->w;
            if(!inMST[v] && w < cost[v]){
                cost[v]=w; parent[v]=u;
                heapPush(h,v,w);        /* push duplicate instead of decrease-key */
            }
        }
    }

    printf("Edges in MST:\n");
    for(int v=0; v<V; v++)
        if(parent[v]!=-1)
            printf("  %s — %s  (%d)\n", g[parent[v]].name, g[v].name, cost[v]);
    printf("Total weight = %lld\n", total);
}

int main(void){
    loadGraph("graphprim.txt");
    prim(0);                 /* start from vertex 0 */
    return 0;
}
