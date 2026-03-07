#include <stdio.h>

#define MAX 100  // Maximum number of vertices

int queue[MAX];
int front = -1;
int rear = -1;
int visited[MAX];
int adj[MAX][MAX];
int n;

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

int dequeue() {
    if (front == -1 || front > rear) {
        return -1;
    }
    int value = queue[front];
    front++;
    return value;
}

void bfs(int start) {
    int v;
    
    enqueue(start);
    
    visited[start] = 1;
    
    while (front != -1 && front <= rear) {
        v = dequeue();
        
        printf("%d ", v);
        for (int i = 0; i < n; i++) {
            if (adj[v][i] == 1 && visited[i] == 0) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
}

int main() {
    int start_node;
    
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    
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
