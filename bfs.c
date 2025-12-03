#include <stdio.h>

#define MAX 100  // Maximum number of vertices

// Global variables to be accessible by all functions
int queue[MAX];
int front = -1;
int rear = -1;
int visited[MAX];
int adj[MAX][MAX]; // Adjacency matrix
int n; // Number of vertices

// Function to add an element to the queue
void enqueue(int v) {
    if (rear == MAX - 1) {
        printf("Queue Overflow\n");
        return;
    }
    if (front == -1) {
        front = 0;
    }
    rear++;
    queue[rear] = v;
}

// Function to remove an element from the queue
int dequeue() {
    if (front == -1 || front > rear) {
        return -1; // Queue is empty
    }
    int value = queue[front];
    front++;
    return value;
}

// Breadth-First Search Logic
void bfs(int start) {
    int v;
    
    // 1. Enqueue the starting node
    enqueue(start);
    
    // 2. Mark the starting node as visited
    visited[start] = 1;
    
    // 3. Loop until the queue is empty
    while (front != -1 && front <= rear) {
        // Remove the current node from the queue
        v = dequeue();
        
        // Print the node we are currently processing
        printf("%d ", v);
        
        // Check all adjacent nodes
        for (int i = 0; i < n; i++) {
            // If there is an edge (adj[v][i] == 1) AND it hasn't been visited yet
            if (adj[v][i] == 1 && visited[i] == 0) {
                enqueue(i);       // Add neighbor to queue
                visited[i] = 1;   // Mark neighbor as visited immediately
            }
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
    
    printf("BFS Traversal: ");
    bfs(start_node);
    printf("\n");
    
    return 0;
}