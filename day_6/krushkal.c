/*
WAP to find the MST of a given graph using Kruskal’s algorithm. Check your
program on a graph whose length matrix is given below. Your program should
use UNION & FIND operations on Disjoint data structure.

   a b c d e f g h i

a  0 4 ∞ ∞ ∞ ∞ ∞ 8 ∞
b  4 0 8 ∞ ∞ ∞ ∞ 11 ∞
c  ∞ 8 0 7 ∞ 4 ∞ ∞ 2
d  ∞ ∞ 7 0 9 14 ∞ ∞ ∞
e  ∞ ∞ ∞ 9 0 10 ∞ ∞ ∞
f  ∞ ∞ 4 14 10 0 2 ∞ ∞
g  ∞ ∞ ∞ ∞ ∞ 2 0 1 6
h  8 11 ∞ ∞ ∞ ∞ 1 0 7
i  ∞ ∞ 2 ∞ ∞ ∞ 6 7 0


*/

#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include<string.h>
#include<stdbool.h>

typedef struct Node {
    int data;
    struct Node* p;
    int rank;
} Node;

typedef struct Edge {
    int u, v, w;
} Edge;

Node* find_set(Node* node) {
    if (node->p != node)
        node->p = find_set(node->p);
    return node->p;
}

void make_set(Node* node) {
    node->p = node;
    node->rank = 0;
}

void Link(Node* node1, Node* node2) {
    if (node1->rank > node2->rank)
        node2->p = node1;
    else {
        node1->p = node2;
        if (node1->rank == node2->rank)
            node2->rank++;
    }
}

void Union(Node* node1, Node* node2) {
    Link(find_set(node1), find_set(node2));
}

int compareEdges(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->w - edgeB->w;
}

int main() {
    int n, edgeCount = 0;
    FILE *fp;
    fp = fopen("input_kruskal.txt", "r");

    fscanf(fp, "%d", &n);

    Node* nodes = (Node*)malloc(n * sizeof(Node));
    for (int i = 0; i < n; i++) {
        nodes[i].data = i;
        make_set(&nodes[i]);
    }

    Edge* Edges = (Edge*)malloc(2 * n * sizeof(Edge));
    char u, v;
    int w;

    while (fscanf(fp, " %c %c %d", &u, &v, &w) != EOF) {
        Edges[edgeCount].u = u - 'a'; 
        Edges[edgeCount].v = v - 'a';
        Edges[edgeCount].w = w;
        edgeCount++;
    }
