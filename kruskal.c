#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int src, dest, weight;
} Edge;

static int compare_edges(const void *a, const void *b) {
    const Edge *ea = a;
    const Edge *eb = b;
    return ea->weight - eb->weight;
}

static int find_set(int *parent, int v) {
    if (parent[v] != v) {
        parent[v] = find_set(parent, parent[v]);
    }
    return parent[v];
}

static void union_sets(int *parent, int *rank, int a, int b) {
    a = find_set(parent, a);
    b = find_set(parent, b);
    if (a != b) {
        if (rank[a] < rank[b]) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        parent[b] = a;
        if (rank[a] == rank[b]) {
            ++rank[a];
        }
    }
}

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

    qsort(edge_list, (size_t)edges, sizeof(Edge), compare_edges);

    int *parent = malloc((size_t)vertices * sizeof(int));
    int *rank = calloc((size_t)vertices, sizeof(int));
    if (!parent || !rank) {
        perror("malloc");
        free(parent);
        free(rank);
        free(edge_list);
        return 1;
    }
    for (int i = 0; i < vertices; ++i) {
        parent[i] = i;
    }

    int mst_edges = 0;
    int total_weight = 0;
    printf("Edges in the MST:\n");
    for (int i = 0; i < edges && mst_edges < vertices - 1; ++i) {
        int u = edge_list[i].src;
        int v = edge_list[i].dest;
        if (find_set(parent, u) != find_set(parent, v)) {
            union_sets(parent, rank, u, v);
            printf("%d - %d (weight %d)\n", u, v, edge_list[i].weight);
            total_weight += edge_list[i].weight;
            ++mst_edges;
        }
    }

    if (mst_edges != vertices - 1) {
        printf("Graph is not connected. MST could not be formed completely.\n");
    }
    printf("Total weight: %d\n", total_weight);

    free(parent);
    free(rank);
    free(edge_list);
    return 0;
}

