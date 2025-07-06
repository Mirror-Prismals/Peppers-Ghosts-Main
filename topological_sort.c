#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int v, e;
    printf("Enter number of vertices: ");
    if (scanf("%d", &v) != 1 || v <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    printf("Enter number of edges: ");
    if (scanf("%d", &e) != 1 || e < 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    int *adj = calloc(v * v, sizeof(int));
    int *indegree = calloc(v, sizeof(int));
    if (!adj || !indegree) {
        perror("calloc");
        free(adj);
        free(indegree);
        return 1;
    }

    for (int i = 0; i < e; ++i) {
        int u, w;
        printf("Enter edge %d (u v): ", i + 1);
        if (scanf("%d %d", &u, &w) != 2 || u < 0 || u >= v || w < 0 || w >= v) {
            fprintf(stderr, "Invalid input.\n");
            free(adj);
            free(indegree);
            return 1;
        }
        if (!adj[u * v + w]) {
            adj[u * v + w] = 1;
            ++indegree[w];
        }
    }

    int *queue = malloc(v * sizeof(int));
    int *order = malloc(v * sizeof(int));
    if (!queue || !order) {
        perror("malloc");
        free(adj);
        free(indegree);
        free(queue);
        free(order);
        return 1;
    }

    int front = 0, back = 0;
    for (int i = 0; i < v; ++i) {
        if (indegree[i] == 0) {
            queue[back++] = i;
        }
    }

    int count = 0;
    while (front < back) {
        int u = queue[front++];
        order[count++] = u;
        for (int w = 0; w < v; ++w) {
            if (adj[u * v + w]) {
                if (--indegree[w] == 0) {
                    queue[back++] = w;
                }
            }
        }
    }

    if (count != v) {
        printf("Cycle detected. No topological order exists.\n");
    } else {
        printf("Topological order:\n");
        for (int i = 0; i < v; ++i) {
            printf("%d%s", order[i], i == v - 1 ? "\n" : " ");
        }
    }

    free(adj);
    free(indegree);
    free(queue);
    free(order);
    return 0;
}
