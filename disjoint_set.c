#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *parent;
    int *rank;
    int size;
} DisjointSet;

static DisjointSet *create_set(int n) {
    DisjointSet *ds = malloc(sizeof(DisjointSet));
    if (!ds) {
        return NULL;
    }
    ds->parent = malloc(n * sizeof(int));
    ds->rank = malloc(n * sizeof(int));
    if (!ds->parent || !ds->rank) {
        free(ds->parent);
        free(ds->rank);
        free(ds);
        return NULL;
    }
    ds->size = n;
    for (int i = 0; i < n; ++i) {
        ds->parent[i] = i;
        ds->rank[i] = 0;
    }
    return ds;
}

static int find_set(DisjointSet *ds, int x) {
    if (ds->parent[x] != x) {
        ds->parent[x] = find_set(ds, ds->parent[x]);
    }
    return ds->parent[x];
}

static void union_set(DisjointSet *ds, int x, int y) {
    int root_x = find_set(ds, x);
    int root_y = find_set(ds, y);
    if (root_x == root_y) {
        return;
    }
    if (ds->rank[root_x] < ds->rank[root_y]) {
        ds->parent[root_x] = root_y;
    } else if (ds->rank[root_x] > ds->rank[root_y]) {
        ds->parent[root_y] = root_x;
    } else {
        ds->parent[root_y] = root_x;
        ds->rank[root_x]++;
    }
}

static void free_set(DisjointSet *ds) {
    if (ds) {
        free(ds->parent);
        free(ds->rank);
        free(ds);
    }
}

int main(void) {
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid number of elements.\n");
        return 1;
    }
    DisjointSet *ds = create_set(n);
    if (!ds) {
        perror("create_set");
        return 1;
    }

    int unions;
    printf("Enter number of union operations: ");
    if (scanf("%d", &unions) != 1 || unions < 0) {
        fprintf(stderr, "Invalid number.\n");
        free_set(ds);
        return 1;
    }
    for (int i = 0; i < unions; ++i) {
        int a, b;
        printf("Union %d (two indices 0-%d): ", i + 1, n - 1);
        if (scanf("%d %d", &a, &b) != 2 || a < 0 || a >= n || b < 0 || b >= n) {
            fprintf(stderr, "Invalid indices.\n");
            free_set(ds);
            return 1;
        }
        union_set(ds, a, b);
    }

    int queries;
    printf("Enter number of connectivity queries: ");
    if (scanf("%d", &queries) != 1 || queries < 0) {
        fprintf(stderr, "Invalid number.\n");
        free_set(ds);
        return 1;
    }
    for (int i = 0; i < queries; ++i) {
        int a, b;
        printf("Query %d (two indices 0-%d): ", i + 1, n - 1);
        if (scanf("%d %d", &a, &b) != 2 || a < 0 || a >= n || b < 0 || b >= n) {
            fprintf(stderr, "Invalid indices.\n");
            free_set(ds);
            return 1;
        }
        if (find_set(ds, a) == find_set(ds, b)) {
            printf("%d and %d are connected.\n", a, b);
        } else {
            printf("%d and %d are not connected.\n", a, b);
        }
    }

    free_set(ds);
    return 0;
}

