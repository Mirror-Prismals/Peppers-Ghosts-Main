#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Edge {
    int src;
    int dest;
    int weight;
};

int main(void) {
    int n, m;
    printf("Enter number of vertices: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    printf("Enter number of edges: ");
    if (scanf("%d", &m) != 1 || m < 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    struct Edge *edges = malloc(m * sizeof(struct Edge));
    if (!edges) {
        perror("malloc");
        return 1;
    }

    printf("Enter edges (src dest weight):\n");
    for (int i = 0; i < m; ++i) {
        if (scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight) != 3 ||
            edges[i].src < 0 || edges[i].src >= n ||
            edges[i].dest < 0 || edges[i].dest >= n) {
            fprintf(stderr, "Invalid edge input.\n");
            free(edges);
            return 1;
        }
    }

    int start;
    printf("Enter start vertex (0-%d): ", n - 1);
    if (scanf("%d", &start) != 1 || start < 0 || start >= n) {
        fprintf(stderr, "Invalid input.\n");
        free(edges);
        return 1;
    }

    int *dist = malloc(n * sizeof(int));
    if (!dist) {
        perror("malloc");
        free(edges);
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;

    for (int i = 1; i < n; ++i) {
        int updated = 0;
        for (int j = 0; j < m; ++j) {
            if (dist[edges[j].src] != INT_MAX &&
                dist[edges[j].src] + edges[j].weight < dist[edges[j].dest]) {
                dist[edges[j].dest] = dist[edges[j].src] + edges[j].weight;
                updated = 1;
            }
        }
        if (!updated) {
            break;
        }
    }

    int has_cycle = 0;
    for (int j = 0; j < m; ++j) {
        if (dist[edges[j].src] != INT_MAX &&
            dist[edges[j].src] + edges[j].weight < dist[edges[j].dest]) {
            has_cycle = 1;
            break;
        }
    }

    if (has_cycle) {
        printf("Graph contains a negative weight cycle\n");
    } else {
        printf("Shortest distances from vertex %d:\n", start);
        for (int i = 0; i < n; ++i) {
            if (dist[i] == INT_MAX) {
                printf("%d: unreachable\n", i);
            } else {
                printf("%d: %d\n", i, dist[i]);
            }
        }
    }

    free(dist);
    free(edges);
    return 0;
}
