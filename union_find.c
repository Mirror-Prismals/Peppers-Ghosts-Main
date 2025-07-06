#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *parent;
    int *rank;
    int size;
} DSU;

static DSU *dsu_create(int size) {
    DSU *d = malloc(sizeof(DSU));
    if (!d) {
        return NULL;
    }
    d->parent = malloc((size_t)size * sizeof(int));
    d->rank = calloc((size_t)size, sizeof(int));
    if (!d->parent || !d->rank) {
        free(d->parent);
        free(d->rank);
        free(d);
        return NULL;
    }
    for (int i = 0; i < size; ++i) {
        d->parent[i] = i;
    }
    d->size = size;
    return d;
}

static int dsu_find(DSU *d, int x) {
    if (d->parent[x] != x) {
        d->parent[x] = dsu_find(d, d->parent[x]);
    }
    return d->parent[x];
}

static void dsu_union(DSU *d, int a, int b) {
    int root_a = dsu_find(d, a);
    int root_b = dsu_find(d, b);
    if (root_a == root_b) {
        return;
    }
    if (d->rank[root_a] < d->rank[root_b]) {
        d->parent[root_a] = root_b;
    } else if (d->rank[root_a] > d->rank[root_b]) {
        d->parent[root_b] = root_a;
    } else {
        d->parent[root_b] = root_a;
        d->rank[root_a]++;
    }
}

static void dsu_free(DSU *d) {
    if (d) {
        free(d->parent);
        free(d->rank);
        free(d);
    }
}

int main(void) {
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid number of elements.\n");
        return 1;
    }
    DSU *dsu = dsu_create(n);
    if (!dsu) {
        perror("dsu_create");
        return 1;
    }
    int q;
    printf("Enter number of operations: ");
    if (scanf("%d", &q) != 1 || q < 0) {
        fprintf(stderr, "Invalid number of operations.\n");
        dsu_free(dsu);
        return 1;
    }
    for (int i = 0; i < q; ++i) {
        char op;
        int a, b;
        printf("Operation %d (format: [u/f] a b): ", i + 1);
        if (scanf(" %c %d %d", &op, &a, &b) != 3 || a < 0 || a >= n || b < 0 || b >= n) {
            fprintf(stderr, "Invalid operation.\n");
            dsu_free(dsu);
            return 1;
        }
        if (op == 'u') {
            dsu_union(dsu, a, b);
        } else if (op == 'f') {
            if (dsu_find(dsu, a) == dsu_find(dsu, b)) {
                printf("%d and %d are connected.\n", a, b);
            } else {
                printf("%d and %d are not connected.\n", a, b);
            }
        } else {
            fprintf(stderr, "Unknown operation '%c'.\n", op);
            dsu_free(dsu);
            return 1;
        }
    }
    dsu_free(dsu);
    return 0;
}

