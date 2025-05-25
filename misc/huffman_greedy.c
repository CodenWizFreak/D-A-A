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

/* -------------- Utility Functions -------------- */

/* Allocate a new heap node */
static MinHeapNode *newNode(unsigned char data, unsigned freq) {
    MinHeapNode *temp = (MinHeapNode *)malloc(sizeof(MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

/* Allocate a min‑heap of given capacity */
static MinHeap *createMinHeap(unsigned capacity) {
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode **)malloc(capacity * sizeof(MinHeapNode *));
    return minHeap;
}

/* Swap two node pointers */
static void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b) {
    MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

/* Standard min‑heapify function */
static void minHeapify(MinHeap *minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < (int)minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < (int)minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}
