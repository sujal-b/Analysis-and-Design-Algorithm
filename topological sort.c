#include <stdio.h>

int main() {
    int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    int graph[n][n], in_degree[n], queue[n], result[n];
    int front = 0, rear = 0, k = 0;

    for (int i = 0; i < n; i++) in_degree[i] = 0;

    printf("\nEnter the Adjacency Matrix (0 for no edge, 1 for edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == 1) {
                in_degree[j]++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0) queue[rear++] = i;
    }

    while (front < rear) {
        int u = queue[front++];
        result[k++] = u;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] == 1) {
                in_degree[v]--;
                if (in_degree[v] == 0) queue[rear++] = v;
            }
        }
    }

    if (k != n) {
        printf("\nError: Cycle detected! Topological sort not possible.\n");
    } else {
        printf("\nTopological Order: ");
        for (int i = 0; i < k; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    }

    return 0;
}