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

/* ---------- global graph ---------- */
Vertex g[MAXV]; int V=0,E=0;

int idx(const char *nm){
    for(int i=0;i<V;i++) if(!strcmp(g[i].name,nm)) return i;
    strcpy(g[V].name,nm); g[V].adj=NULL; return V++;
}
void addEdge(int u,int v,int w){
    Edge *e=malloc(sizeof(Edge)); e->to=v; e->w=w; e->next=g[u].adj; g[u].adj=e;
}

void load(const char *fn){
    FILE *fp=fopen(fn,"r"); if(!fp){perror(fn);exit(1);}
    int declared; if(fscanf(fp,"%d",&declared)!=1){fprintf(stderr,"Bad file\n");exit(1);}
    char a[MAXNAME],b[MAXNAME]; int w;
    while(fscanf(fp,"%s %s %d",a,b,&w)==3){
        int u=idx(a), v=idx(b);
        addEdge(u,v,w); addEdge(v,u,w); ++E;
    }
    fclose(fp);
}

/* ---------- Prim (with decrease-key) ---------- */
void prim(int s){
    int parent[MAXV], key[MAXV], inMST[MAXV]={0};
    for(int i=0;i<V;i++){ key[i]=INT_MAX; parent[i]=-1; }
    key[s]=0;
    MinHeap *h=heapCreate(V,key);
    for(int v=0;v<V;v++) heapInsert(h,v);

    long long total=0;
    while(!heapEmpty(h)){
        int u=heapExtractMin(h);
        inMST[u]=1; total+=key[u];
        for(Edge*e=g[u].adj;e;e=e->next){
            int v=e->to,w=e->w;
            if(!inMST[v] && w<key[v])
                heapDecreaseKey(h,v,w), parent[v]=u;
        }
    }
    printf("Edges in MST:\n");
    for(int v=0;v<V;v++) if(parent[v]!=-1)
        printf("  %s — %s  (%d)\n",g[parent[v]].name,g[v].name,key[v]);
    printf("Total weight = %lld\n",total);
}
