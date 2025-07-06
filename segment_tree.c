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

static void update(int *tree, int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node] = val;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid) {
            update(tree, 2 * node, start, mid, idx, val);
        } else {
            update(tree, 2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

static int query(int *tree, int node, int start, int end, int L, int R) {
    if (R < start || end < L) {
        return 0;
    }
    if (L <= start && end <= R) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    int p1 = query(tree, 2 * node, start, mid, L, R);
    int p2 = query(tree, 2 * node + 1, mid + 1, end, L, R);
    return p1 + p2;
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
    if (!arr || !tree) {
        perror("malloc");
        free(arr);
        free(tree);
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(arr);
            free(tree);
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
        return 1;
    }
    for (int i = 0; i < q; ++i) {
        char op;
        printf("Operation %d (format: [u/q] args): ", i + 1);
        if (scanf(" %c", &op) != 1) {
            fprintf(stderr, "Invalid operation.\n");
            free(arr);
            free(tree);
            return 1;
        }
        if (op == 'u') {
            int idx, val;
            if (scanf("%d %d", &idx, &val) != 2 || idx < 0 || idx >= n) {
                fprintf(stderr, "Invalid update.\n");
                free(arr);
                free(tree);
                return 1;
            }
            update(tree, 1, 0, n - 1, idx, val);
        } else if (op == 'q') {
            int l, r;
            if (scanf("%d %d", &l, &r) != 2 || l < 0 || r >= n || l > r) {
                fprintf(stderr, "Invalid query.\n");
                free(arr);
                free(tree);
                return 1;
            }
            printf("Sum [%d, %d] = %d\n", l, r, query(tree, 1, 0, n - 1, l, r));
        } else {
            fprintf(stderr, "Unknown operation '%c'.\n", op);
            free(arr);
            free(tree);
            return 1;
        }
    }
    free(arr);
    free(tree);
    return 0;
}

