#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* A Huffman tree node */
typedef struct MinHeapNode {
    unsigned char data;            /* Stored character */
    unsigned freq;                 /* Frequency of the character */
    struct MinHeapNode *left, *right; /* Left and right child */
} MinHeapNode;

/* Min‑heap: collection of heap (or Huffman tree) nodes */
typedef struct MinHeap {
    unsigned size;      /* Current number of nodes */
    unsigned capacity;  /* Heap capacity */
    MinHeapNode **array; /* Array of node pointers */
} MinHeap;
