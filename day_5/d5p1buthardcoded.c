#include <stdio.h>      // For input/output functions
#include <stdlib.h>     // For general utilities like malloc, free
#include <limits.h>     // For defining max integer value (not used directly here)
#include <string.h>     // For string manipulation (though not directly used here)

#define V 5                 // Number of vertices
#define INF_VALUE 99999     // Representation of infinity for unreachable paths

// Structure to represent an edge with a destination vertex and its weight
typedef struct {
    int vertex;
    int weight;
} Edge;

// Structure to represent the adjacency list for each vertex
typedef struct {
    Edge edges[V];      // List of edges from this vertex
    int edge_count;     // Number of edges from this vertex
} AdjList;

// Node of a min-heap (used as priority queue in Dijkstra)
typedef struct {
    int vertex;
    int distance;       // Distance value from source
} HeapNode;

// Priority queue (min-heap) structure
typedef struct {
    HeapNode data[V];   // Array to hold heap nodes
    int size;           // Current size of heap
} MinHeap;

// Swap two heap nodes
void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Move the node at 'index' up to maintain min-heap property
void heapify_up(MinHeap *heap, int index) {
    if (index && heap->data[index].distance < heap->data[(index - 1) / 2].distance) {
        swap(&heap->data[index], &heap->data[(index - 1) / 2]);
        heapify_up(heap, (index - 1) / 2);  // Recursive call
    }
}

// Move the node at 'index' down to maintain min-heap property
void heapify_down(MinHeap *heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->data[left].distance < heap->data[smallest].distance)
        smallest = left;

    if (right < heap->size && heap->data[right].distance < heap->data[smallest].distance)
        smallest = right;

    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        heapify_down(heap, smallest);  // Recursive call
    }
}

// Insert a new vertex with its distance into the min-heap
void insert(MinHeap *heap, int vertex, int distance) {
    heap->data[heap->size].vertex = vertex;
    heap->data[heap->size].distance = distance;
    heapify_up(heap, heap->size++);  // Increase heap size
}

// Remove and return the vertex with the minimum distance from the heap
HeapNode extract_min(MinHeap *heap) {
    HeapNode root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];  // Replace root with last node
    heapify_down(heap, 0);  // Restore heap property
    return root;
}

// Check if the heap is empty
int is_empty(MinHeap *heap) {
    return heap->size == 0;
}

void dijkstra(AdjList adj[], int source) {
    int dist[V];         // Stores shortest distance from source to each vertex
    int prev[V];         // Stores the previous vertex in the shortest path
    MinHeap heap = { .size = 0 };  // Initialize empty min-heap
    
    // Initialize distances to infinity and no predecessors
    for (int i = 0; i < V; i++) {
        dist[i] = INF_VALUE;
        prev[i] = -1;
    }

    dist[source] = 0;           // Distance to source is zero
    insert(&heap, source, 0);   // Add source to heap

    // Main loop of Dijkstra
    while (!is_empty(&heap)) {
        HeapNode node = extract_min(&heap);  // Get vertex with smallest distance
        int u = node.vertex;

        // Relax all adjacent vertices of u
        for (int i = 0; i < adj[u].edge_count; i++) {
            Edge e = adj[u].edges[i];
            int v = e.vertex;
            int weight = e.weight;

            if (dist[u] + weight < dist[v]) {     // Relaxation step
                dist[v] = dist[u] + weight;       // Update distance
                prev[v] = u;                      // Update path
                insert(&heap, v, dist[v]);        // Add to heap
            }
        }
    }

    // Display all shortest paths from source
    printf("Shortest paths from vertex %c:\n", 's' + source);  // Print header
    for (int i = 0; i < V; i++) {
        if (i == source) continue;

        if (dist[i] == INF_VALUE) {
            printf("%c -> %c: No path\n", 's' + source, 's' + i);
            continue;
        }

        // Reconstruct path from source to i
        int path[V], count = 0;
        for (int v = i; v != -1; v = prev[v])
            path[count++] = v;

        // Print path in correct order
        for (int j = count - 1; j >= 0; j--) {
            printf("%c", 's' + path[j]);
            if (j != 0) printf(" -> ");
        }
        printf(" (Cost: %d)\n", dist[i]);
    }
}

void create_adj_list(AdjList adj[]) {
    // Adjacency matrix with weights (INF_VALUE for no edge)
    int matrix[V][V] = {
        {  0, 10, INF_VALUE,  5, INF_VALUE },  // s
        { INF_VALUE,  0,  1,  2, INF_VALUE },  // t
        { INF_VALUE, INF_VALUE, 0, INF_VALUE, 4 },  // x
        { INF_VALUE, 3, 9, 0, 2 },  // y
        { 7, INF_VALUE, 6, INF_VALUE, 0 }   // z
    };

    // Convert matrix to adjacency list
    for (int i = 0; i < V; i++) {
        adj[i].edge_count = 0;  // Reset edge count
        for (int j = 0; j < V; j++) {
            if (matrix[i][j] != INF_VALUE && i != j) {
                adj[i].edges[adj[i].edge_count].vertex = j;
                adj[i].edges[adj[i].edge_count].weight = matrix[i][j];
                adj[i].edge_count++;  // Add edge to list
            }
        }
    }
}

int main() {
    AdjList adj[V];           // Adjacency list for the graph
    create_adj_list(adj);     // Populate it from matrix

    char src_char;
    printf("Enter source vertex (s, t, u, v, w): ");
    scanf(" %c", &src_char);               // Read input character for source
    int source = src_char - 's';           // Convert char to index (assuming 's' starts at 0)

    if (source < 0 || source >= V) {
        printf("Invalid source vertex.\n");  // Input validation
        return 1;
    }

    dijkstra(adj, source);  // Run the algorithm
    return 0;
}
