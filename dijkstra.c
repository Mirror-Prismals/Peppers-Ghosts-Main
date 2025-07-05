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

    int **graph = malloc(n * sizeof(int*));
    if (!graph) {
        perror("malloc");
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        graph[i] = malloc(n * sizeof(int));
        if (!graph[i]) {
            perror("malloc");
            for (int j = 0; j < i; ++j) free(graph[j]);
            free(graph);
            return 1;
        }
    }

    printf("Enter adjacency matrix (0 for no edge):\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (scanf("%d", &graph[i][j]) != 1 || graph[i][j] < 0) {
                fprintf(stderr, "Invalid input.\n");
                for (int k = 0; k < n; ++k) free(graph[k]);
                free(graph);
                return 1;
            }
        }
    }

    int start;
    printf("Enter start vertex (0-%d): ", n - 1);
    if (scanf("%d", &start) != 1 || start < 0 || start >= n) {
        fprintf(stderr, "Invalid input.\n");
        for (int k = 0; k < n; ++k) free(graph[k]);
        free(graph);
        return 1;
    }

    int *dist = malloc(n * sizeof(int));
    int *visited = calloc(n, sizeof(int));
    if (!dist || !visited) {
        perror("malloc");
        free(dist);
        free(visited);
        for (int k = 0; k < n; ++k) free(graph[k]);
        free(graph);
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;

    for (int count = 0; count < n - 1; ++count) {
        int u = -1;
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }
        if (u == -1 || dist[u] == INT_MAX) {
            break;
        }
        visited[u] = 1;
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] > 0 && !visited[v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("Shortest distances from vertex %d:\n", start);
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INT_MAX) {
            printf("%d: unreachable\n", i);
        } else {
            printf("%d: %d\n", i, dist[i]);
        }
    }

    free(dist);
    free(visited);
    for (int i = 0; i < n; ++i) {
        free(graph[i]);
    }
    free(graph);
    return 0;
}

