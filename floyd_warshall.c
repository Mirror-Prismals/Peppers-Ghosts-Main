#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void) {
    int n;
    printf("Enter number of vertices: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    int **graph = malloc(n * sizeof(int *));
    int **dist = malloc(n * sizeof(int *));
    if (!graph || !dist) {
        perror("malloc");
        free(graph); free(dist);
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        graph[i] = malloc(n * sizeof(int));
        dist[i] = malloc(n * sizeof(int));
        if (!graph[i] || !dist[i]) {
            perror("malloc");
            for (int j = 0; j <= i; ++j) {
                free(graph[j]);
                free(dist[j]);
            }
            free(graph); free(dist);
            return 1;
        }
    }

    printf("Enter adjacency matrix (0 for no edge):\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (scanf("%d", &graph[i][j]) != 1 || graph[i][j] < 0) {
                fprintf(stderr, "Invalid input.\n");
                for (int k = 0; k < n; ++k) { free(graph[k]); free(dist[k]); }
                free(graph); free(dist);
                return 1;
            }
        }
    }

    const int INF = INT_MAX / 2;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                dist[i][j] = 0;
            } else if (graph[i][j] > 0) {
                dist[i][j] = graph[i][j];
            } else {
                dist[i][j] = INF;
            }
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    printf("Shortest distance matrix:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INF) {
                printf("INF ");
            } else {
                printf("%d ", dist[i][j]);
            }
        }
        putchar('\n');
    }

    for (int i = 0; i < n; ++i) {
        free(graph[i]);
        free(dist[i]);
    }
    free(graph);
    free(dist);
    return 0;
}

