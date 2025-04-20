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
