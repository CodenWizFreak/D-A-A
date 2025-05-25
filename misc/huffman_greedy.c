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

static int isSizeOne(MinHeap *minHeap) { return (minHeap->size == 1); }

/* Extract the minimum value (root) from heap */
static MinHeapNode *extractMin(MinHeap *minHeap) {
    MinHeapNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

/* Insert a new node to Min‑Heap */
static void insertMinHeap(MinHeap *minHeap, MinHeapNode *node) {
    ++minHeap->size;
    int i = (int)minHeap->size - 1;

    while (i && node->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}
