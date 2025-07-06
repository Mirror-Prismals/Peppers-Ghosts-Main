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
    if (!graph) {
        perror("malloc");
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        graph[i] = malloc(n * sizeof(int));
        if (!graph[i]) {
            perror("malloc");
            for (int j = 0; j < i; ++j) {
                free(graph[j]);
            }
            free(graph);
            return 1;
        }
    }

    printf("Enter adjacency matrix (0 for no edge):\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (scanf("%d", &graph[i][j]) != 1 || graph[i][j] < 0) {
                fprintf(stderr, "Invalid input.\n");
                for (int k = 0; k < n; ++k) {
                    free(graph[k]);
                }
                free(graph);
                return 1;
            }
        }
    }

    int start;
    printf("Enter start vertex (0-%d): ", n - 1);
    if (scanf("%d", &start) != 1 || start < 0 || start >= n) {
        fprintf(stderr, "Invalid input.\n");
        for (int k = 0; k < n; ++k) {
            free(graph[k]);
        }
        free(graph);
        return 1;
    }

    int *parent = malloc(n * sizeof(int));
    int *key = malloc(n * sizeof(int));
    int *in_mst = calloc(n, sizeof(int));
    if (!parent || !key || !in_mst) {
        perror("malloc");
        free(parent); free(key); free(in_mst);
        for (int k = 0; k < n; ++k) {
            free(graph[k]);
        }
        free(graph);
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        key[i] = INT_MAX;
        parent[i] = -1;
    }
    key[start] = 0;

    for (int count = 0; count < n; ++count) {
        int u = -1;
        for (int i = 0; i < n; ++i) {
            if (!in_mst[i] && (u == -1 || key[i] < key[u])) {
                u = i;
            }
        }
        if (u == -1 || key[u] == INT_MAX) {
            break;
        }
        in_mst[u] = 1;
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] > 0 && !in_mst[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    printf("Edges in the MST:\n");
    int total_weight = 0;
    int edges = 0;
    for (int v = 0; v < n; ++v) {
        if (v != start && parent[v] != -1) {
            printf("%d - %d (weight %d)\n", parent[v], v, graph[v][parent[v]]);
            total_weight += graph[v][parent[v]];
            ++edges;
        }
    }

    if (edges != n - 1) {
        printf("Graph is not connected. MST could not be formed completely.\n");
    }
    printf("Total weight: %d\n", total_weight);

    for (int i = 0; i < n; ++i) {
        free(graph[i]);
    }
    free(graph);
    free(parent);
    free(key);
    free(in_mst);
    return 0;
}

