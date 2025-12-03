#include <stdio.h>

#define MAX 100  // Maximum number of vertices

// Global variables
int visited[MAX];
int adj[MAX][MAX]; // Adjacency matrix
int n; // Number of vertices

// Depth-First Search Logic (Recursive)
void dfs(int v) {
    // 1. Mark the current node as visited immediately
    visited[v] = 1;
    
    // 2. Print the node
    printf("%d ", v);
    
    // 3. Visit all unvisited neighbors
    for (int i = 0; i < n; i++) {
        // If there is an edge to 'i' AND 'i' is not visited yet
        if (adj[v][i] == 1 && visited[i] == 0) {
            // Recursive call: Go deep into this neighbor
            dfs(i); 
        }
    }
}

int main() {
    int start_node;
    
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    
    // Initialize visited array to 0 (unvisited)
    for(int i = 0; i < n; i++) {
        visited[i] = 0;
    }
    
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }
    
    printf("Enter start node: ");
    scanf("%d", &start_node);
    
    printf("DFS Traversal: ");
    dfs(start_node); 
    printf("\n");
    
    return 0;
}