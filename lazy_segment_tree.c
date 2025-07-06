#include <stdio.h>
#include <stdlib.h>

static void build(int *tree, int *arr, int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(tree, arr, 2 * node, start, mid);
        build(tree, arr, 2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

static void apply_lazy(int *tree, int *lazy, int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

static void update_range(int *tree, int *lazy, int node, int start, int end,
                         int l, int r, int val) {
    apply_lazy(tree, lazy, node, start, end);
    if (start > end || start > r || end < l) {
        return;
    }
    if (l <= start && end <= r) {
        tree[node] += (end - start + 1) * val;
        if (start != end) {
            lazy[2 * node] += val;
            lazy[2 * node + 1] += val;
        }
        return;
    }
    int mid = (start + end) / 2;
    update_range(tree, lazy, 2 * node, start, mid, l, r, val);
    update_range(tree, lazy, 2 * node + 1, mid + 1, end, l, r, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

static int query_range(int *tree, int *lazy, int node, int start, int end,
                       int l, int r) {
    if (start > end || start > r || end < l) {
        return 0;
    }
    apply_lazy(tree, lazy, node, start, end);
    if (l <= start && end <= r) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    int left = query_range(tree, lazy, 2 * node, start, mid, l, r);
    int right = query_range(tree, lazy, 2 * node + 1, mid + 1, end, l, r);
    return left + right;
}

int main(void) {
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid number of elements.\n");
        return 1;
    }
    int *arr = malloc((size_t)n * sizeof(int));
    int *tree = malloc((size_t)(4 * n) * sizeof(int));
    int *lazy = calloc((size_t)(4 * n), sizeof(int));
    if (!arr || !tree || !lazy) {
        perror("malloc");
        free(arr);
        free(tree);
        free(lazy);
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(arr);
            free(tree);
            free(lazy);
            return 1;
        }
    }
    build(tree, arr, 1, 0, n - 1);

    int q;
    printf("Enter number of operations: ");
    if (scanf("%d", &q) != 1 || q < 0) {
        fprintf(stderr, "Invalid number of operations.\n");
        free(arr);
        free(tree);
        free(lazy);
        return 1;
    }
    for (int i = 0; i < q; ++i) {
        char op;
        printf("Operation %d (format: [u/q] args): ", i + 1);
        if (scanf(" %c", &op) != 1) {
            fprintf(stderr, "Invalid operation.\n");
            free(arr);
            free(tree);
            free(lazy);
            return 1;
        }
        if (op == 'u') {
            int l, r, val;
            if (scanf("%d %d %d", &l, &r, &val) != 3 || l < 0 || r >= n || l > r) {
                fprintf(stderr, "Invalid update.\n");
                free(arr);
                free(tree);
                free(lazy);
                return 1;
            }
            update_range(tree, lazy, 1, 0, n - 1, l, r, val);
        } else if (op == 'q') {
            int l, r;
            if (scanf("%d %d", &l, &r) != 2 || l < 0 || r >= n || l > r) {
                fprintf(stderr, "Invalid query.\n");
                free(arr);
                free(tree);
                free(lazy);
                return 1;
            }
            printf("Sum [%d, %d] = %d\n", l, r,
                   query_range(tree, lazy, 1, 0, n - 1, l, r));
        } else {
            fprintf(stderr, "Unknown operation '%c'.\n", op);
            free(arr);
            free(tree);
            free(lazy);
            return 1;
        }
    }

    free(arr);
    free(tree);
    free(lazy);
    return 0;
}

