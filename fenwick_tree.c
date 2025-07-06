#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int *tree;
} FenwickTree;

FenwickTree fenwick_create(int size) {
    FenwickTree ft;
    ft.size = size;
    ft.tree = calloc(size + 1, sizeof(int));
    if (!ft.tree) {
        perror("calloc");
        exit(1);
    }
    return ft;
}

void fenwick_update(FenwickTree *ft, int index, int delta) {
    for (; index <= ft->size; index += index & -index) {
        ft->tree[index] += delta;
    }
}

int fenwick_sum(const FenwickTree *ft, int index) {
    int result = 0;
    for (; index > 0; index -= index & -index) {
        result += ft->tree[index];
    }
    return result;
}

int fenwick_range_sum(const FenwickTree *ft, int left, int right) {
    return fenwick_sum(ft, right) - fenwick_sum(ft, left - 1);
}

void fenwick_destroy(FenwickTree *ft) {
    free(ft->tree);
    ft->tree = NULL;
    ft->size = 0;
}

int main(void) {
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid size.\n");
        return 1;
    }
    FenwickTree ft = fenwick_create(n);
    for (int i = 1; i <= n; ++i) {
        int value;
        printf("Value %d: ", i);
        if (scanf("%d", &value) != 1) {
            fprintf(stderr, "Invalid input.\n");
            fenwick_destroy(&ft);
            return 1;
        }
        fenwick_update(&ft, i, value);
    }

    printf("Prefix sums:\n");
    for (int i = 1; i <= n; ++i) {
        printf("%d: %d\n", i, fenwick_sum(&ft, i));
    }

    int l, r;
    printf("Query range [l r]: ");
    if (scanf("%d %d", &l, &r) == 2 && l >= 1 && r >= l && r <= n) {
        printf("Sum of [%d, %d] = %d\n", l, r, fenwick_range_sum(&ft, l, r));
    }

    fenwick_destroy(&ft);
    return 0;
}
