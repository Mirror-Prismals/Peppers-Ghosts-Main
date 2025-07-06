#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int src, dest, weight;
} Edge;

int main(void) {
    int vertices, edges;
    printf("Enter number of vertices: ");
    if (scanf("%d", &vertices) != 1 || vertices <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    printf("Enter number of edges: ");
    if (scanf("%d", &edges) != 1 || edges < 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    Edge *edge_list = malloc((size_t)edges * sizeof(Edge));
    if (!edge_list) {
        perror("malloc");
        return 1;
    }

    for (int i = 0; i < edges; ++i) {
        int u, v, w;
        printf("Edge %d (src dest weight): ", i + 1);
        if (scanf("%d %d %d", &u, &v, &w) != 3 ||
            u < 0 || u >= vertices || v < 0 || v >= vertices) {
            fprintf(stderr, "Invalid edge.\n");
            free(edge_list);
            return 1;
        }
        edge_list[i].src = u;
        edge_list[i].dest = v;
        edge_list[i].weight = w;
    }

    int start;
    printf("Enter start vertex (0-%d): ", vertices - 1);
    if (scanf("%d", &start) != 1 || start < 0 || start >= vertices) {
        fprintf(stderr, "Invalid input.\n");
        free(edge_list);
        return 1;
    }

    int *dist = malloc((size_t)vertices * sizeof(int));
    if (!dist) {
        perror("malloc");
        free(edge_list);
        return 1;
    }

    for (int i = 0; i < vertices; ++i) {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;

    for (int i = 0; i < vertices - 1; ++i) {
        int updated = 0;
        for (int j = 0; j < edges; ++j) {
            int u = edge_list[j].src;
            int v = edge_list[j].dest;
            int w = edge_list[j].weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                updated = 1;
            }
        }
        if (!updated) {
            break;
        }
    }

    for (int j = 0; j < edges; ++j) {
        int u = edge_list[j].src;
        int v = edge_list[j].dest;
        int w = edge_list[j].weight;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            printf("Graph contains a negative weight cycle.\n");
            free(dist);
            free(edge_list);
            return 0;
        }
    }

    printf("Shortest distances from vertex %d:\n", start);
    for (int i = 0; i < vertices; ++i) {
        if (dist[i] == INT_MAX) {
            printf("%d: unreachable\n", i);
        } else {
            printf("%d: %d\n", i, dist[i]);
        }
    }

    free(dist);
    free(edge_list);
    return 0;
}

