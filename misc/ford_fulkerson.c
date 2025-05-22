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
