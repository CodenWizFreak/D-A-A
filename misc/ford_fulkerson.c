// Maximum flow from a to f is: 23


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX 26 // for alphabet nodes

int bfs(int rGraph[MAX][MAX], int s, int t, int parent[], int V) {
    int visited[MAX] = {0};
    int queue[MAX], front = 0, rear = 0;

    queue[rear++] = s;
    visited[s] = 1;
    parent[s] = -1;
    while (front < rear){
        int u = queue[front++];
        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = 1;
            }
        }
    }

    return visited[t];
}

int fordFulkerson(int graph[MAX][MAX], int s, int t, int V) {
    int u, v;
    int rGraph[MAX][MAX];

    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int parent[MAX];
    int max_flow = 0;
    while (bfs(rGraph, s, t, parent, V)) {
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            if (rGraph[u][v] < path_flow)
                path_flow = rGraph[u][v];
        }
    for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int charToIndex(char c) {
    return c - 'a';
}

int main() {
    FILE *file = fopen("fdf.txt", "r");
    if (!file) {
        printf("Error opening fdf.txt\n");
        return 1;
    }
    int V;
    fscanf(file, "%d", &V);

    int graph[MAX][MAX] = {0};

    char u, v;
    int cap;
    while (fscanf(file, " %c %c %d", &u, &v, &cap) == 3) {
        graph[charToIndex(u)][charToIndex(v)] = cap;
    }
    fclose(file);

    int source = charToIndex('a');
    int sink = charToIndex('f');

    int maxFlow = fordFulkerson(graph, source, sink, V);
    printf("Maximum flow from a to f is: %d\n", maxFlow);

    return 0;
}
