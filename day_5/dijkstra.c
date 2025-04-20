/*
WAP to implement Dijkstra’s Algorithm for Single Source Shortest path problem. Your program should use priority queue implementation. Check your program on the following directed graph. The graph should be implemented by adjacency list.

   s    t    x    y    z
s  0   10   INF   5   INF
t  INF  0    1    2   INF
x  INF INF   0   INF   4
y  INF  3    9    0    2
z  7   INF   6   INF   0



*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define V 5
#define INF_VALUE 99999

typedef struct {
    int vertex;
    int weight;
} Edge;

typedef struct {
    Edge edges[V];
    int edge_count;
} AdjList;

typedef struct {
    int vertex;
    int distance;
} HeapNode;

typedef struct {
    HeapNode data[V];
    int size;
} MinHeap;

void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MinHeap *heap, int index) {
    if (index && heap->data[index].distance < heap->data[(index - 1) / 2].distance) {
        swap(&heap->data[index], &heap->data[(index - 1) / 2]);
        heapify_up(heap, (index - 1) / 2);
    }
}

void heapify_down(MinHeap *heap, int index) {
    int smallest = index;
    int left = 2*index + 1;
    int right = 2*index + 2;

    if (left < heap->size && heap->data[left].distance < heap->data[smallest].distance)
        smallest = left;

    if (right < heap->size && heap->data[right].distance < heap->data[smallest].distance)
        smallest = right;

    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        heapify_down(heap, smallest);
    }
}

void insert(MinHeap *heap, int vertex, int distance) {
    heap->data[heap->size].vertex = vertex;
    heap->data[heap->size].distance = distance;
    heapify_up(heap, heap->size++);
}

HeapNode extract_min(MinHeap *heap) {
    HeapNode root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    heapify_down(heap, 0);
    return root;
}

int is_empty(MinHeap *heap) {
    return heap->size == 0;
}

void dijkstra(AdjList adj[], int source) {
    int dist[V];
    int prev[V];
    MinHeap heap = { .size = 0 };
    
    for (int i = 0; i < V; i++) {
        dist[i] = INF_VALUE;
        prev[i] = -1;
    }
    dist[source] = 0;
    insert(&heap, source, 0);

    while (!is_empty(&heap)) {
        HeapNode node = extract_min(&heap);
        int u = node.vertex;

        for (int i = 0; i < adj[u].edge_count; i++) {
            Edge e = adj[u].edges[i];
            int v = e.vertex;
            int weight = e.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                insert(&heap, v, dist[v]);
            }
        }
    }
    printf("Shortest paths from vertex %c:\n", 's' + source);
    for (int i = 0; i < V; i++) {
        if (i == source) continue;
        printf("%c -> ", 's' + source);
        int path[V], count = 0;
        for (int v = i; v != -1; v = prev[v])
            path[count++] = v;
        for (int j = count - 1; j >= 0; j--) {
            printf("%c", 's' + path[j]);
            if (j != 0) printf(" -> ");
        }
        printf(" (Cost: %d)\n", dist[i]);
    }
}


   
