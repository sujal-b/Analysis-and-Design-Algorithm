#include <stdio.h>
#include <stdbool.h>

int main() {
    int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    bool R[n][n];

    printf("\nEnter the Adjacency Matrix (0 for no edge, 1 for edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d",&R[i][j]);
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                R[i][j] = R[i][j] || (R[i][k] && R[k][j]);
            }
        }
    }

    printf("\nTransitive Closure Matrix (R):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", R[i][j] ? 1 : 0);
        }
        printf("\n");
    }

    return 0;
}