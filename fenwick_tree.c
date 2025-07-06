#include <stdio.h>
#include <stdlib.h>

static void fenwick_update(int *tree, int n, int index, int delta) {
    for (; index <= n; index += index & -index) {
        tree[index] += delta;
    }
}

static int fenwick_query(int *tree, int index) {
    int sum = 0;
    for (; index > 0; index -= index & -index) {
        sum += tree[index];
    }
    return sum;
}

int main(void) {
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid number of elements.\n");
        return 1;
    }

    int *tree = calloc((size_t)n + 1, sizeof(int));
    if (!tree) {
        perror("calloc");
        return 1;
    }

    printf("Enter %d initial values:\n", n);
    for (int i = 1; i <= n; ++i) {
        int val;
        if (scanf("%d", &val) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(tree);
            return 1;
        }
        fenwick_update(tree, n, i, val);
    }

    int q;
    printf("Enter number of operations: ");
    if (scanf("%d", &q) != 1 || q < 0) {
        fprintf(stderr, "Invalid number of operations.\n");
        free(tree);
        return 1;
    }

    for (int i = 0; i < q; ++i) {
        char op;
        printf("Operation %d (format: [u/q] index [value]): ", i + 1);
        if (scanf(" %c", &op) != 1) {
            fprintf(stderr, "Invalid operation.\n");
            free(tree);
            return 1;
        }
        if (op == 'u') {
            int idx, delta;
            if (scanf("%d %d", &idx, &delta) != 2 || idx <= 0 || idx > n) {
                fprintf(stderr, "Invalid update.\n");
                free(tree);
                return 1;
            }
            fenwick_update(tree, n, idx, delta);
        } else if (op == 'q') {
            int idx;
            if (scanf("%d", &idx) != 1 || idx < 0 || idx > n) {
                fprintf(stderr, "Invalid query.\n");
                free(tree);
                return 1;
            }
            printf("Prefix sum up to %d = %d\n", idx, fenwick_query(tree, idx));
        } else {
            fprintf(stderr, "Unknown operation '%c'.\n", op);
            free(tree);
            return 1;
        }
    }

    free(tree);
    return 0;
}

