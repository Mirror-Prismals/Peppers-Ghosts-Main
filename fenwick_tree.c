#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    long long *tree;
} Fenwick;

static Fenwick *fenwick_create(int size) {
    Fenwick *f = malloc(sizeof(Fenwick));
    if (!f) {
        return NULL;
    }
    f->tree = calloc((size_t)size + 1, sizeof(long long));
    if (!f->tree) {
        free(f);
        return NULL;
    }
    f->size = size;
    return f;
}

static void fenwick_update(Fenwick *f, int idx, long long delta) {
    for (; idx <= f->size; idx += idx & -idx) {
        f->tree[idx] += delta;
    }
}

static long long fenwick_sum(const Fenwick *f, int idx) {
    long long res = 0;
    for (; idx > 0; idx -= idx & -idx) {
        res += f->tree[idx];
    }
    return res;
}

static long long fenwick_range_sum(const Fenwick *f, int l, int r) {
    if (l > r) {
        return 0;
    }
    if (l < 1) {
        l = 1;
    }
    if (r > f->size) {
        r = f->size;
    }
    return fenwick_sum(f, r) - fenwick_sum(f, l - 1);
}

static void fenwick_free(Fenwick *f) {
    if (f) {
        free(f->tree);
        free(f);
    }
}

int main(void) {
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid number of elements.\n");
        return 1;
    }
    Fenwick *ft = fenwick_create(n);
    if (!ft) {
        perror("fenwick_create");
        return 1;
    }
    printf("Enter %d integers:\n", n);
    for (int i = 1; i <= n; ++i) {
        long long val;
        if (scanf("%lld", &val) != 1) {
            fprintf(stderr, "Invalid input.\n");
            fenwick_free(ft);
            return 1;
        }
        fenwick_update(ft, i, val);
    }
    int q;
    printf("Enter number of operations: ");
    if (scanf("%d", &q) != 1 || q < 0) {
        fprintf(stderr, "Invalid number of operations.\n");
        fenwick_free(ft);
        return 1;
    }
    for (int i = 0; i < q; ++i) {
        char op;
        printf("Operation %d (u idx delta / q l r): ", i + 1);
        if (scanf(" %c", &op) != 1) {
            fprintf(stderr, "Invalid operation.\n");
            fenwick_free(ft);
            return 1;
        }
        if (op == 'u') {
            int idx;
            long long delta;
            if (scanf("%d %lld", &idx, &delta) != 2 || idx < 1 || idx > n) {
                fprintf(stderr, "Invalid update parameters.\n");
                fenwick_free(ft);
                return 1;
            }
            fenwick_update(ft, idx, delta);
        } else if (op == 'q') {
            int l, r;
            if (scanf("%d %d", &l, &r) != 2 || l < 1 || r < l || r > n) {
                fprintf(stderr, "Invalid query parameters.\n");
                fenwick_free(ft);
                return 1;
            }
            long long ans = fenwick_range_sum(ft, l, r);
            printf("Sum[%d,%d] = %lld\n", l, r, ans);
        } else {
            fprintf(stderr, "Unknown operation '%c'.\n", op);
            fenwick_free(ft);
            return 1;
        }
    }
    fenwick_free(ft);
    return 0;
}
