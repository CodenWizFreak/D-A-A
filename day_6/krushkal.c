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
