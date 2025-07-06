#include <stdio.h>
#include <stdlib.h>

/*
 * Simple Fenwick Tree (Binary Indexed Tree) implementation.
 * Supports point updates and prefix sum queries in O(log n) time.
 */

static int *fenwick;
static size_t size;

static void fenwick_init(size_t n) {
    size = n + 1; // 1-indexed tree
    fenwick = calloc(size, sizeof(int));
    if (!fenwick) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
}

static void fenwick_update(size_t index, int delta) {
    for (size_t i = index + 1; i < size; i += i & -i) {
        fenwick[i] += delta;
    }
}

static int fenwick_sum(size_t index) {
    int result = 0;
    for (size_t i = index + 1; i > 0; i -= i & -i) {
        result += fenwick[i];
    }
    return result;
}

static int fenwick_range_sum(size_t left, size_t right) {
    if (right < left) return 0;
    return fenwick_sum(right) - (left == 0 ? 0 : fenwick_sum(left - 1));
}

int main(void) {
    size_t n;
    printf("Enter number of elements: ");
    if (scanf("%zu", &n) != 1 || n == 0) {
        fprintf(stderr, "Invalid size.\n");
        return EXIT_FAILURE;
    }

    fenwick_init(n);
    int *arr = calloc(n, sizeof(int));
    if (!arr) {
        perror("calloc");
        return EXIT_FAILURE;
    }

    printf("Enter %zu integers:\n", n);
    for (size_t i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(arr);
            return EXIT_FAILURE;
        }
        fenwick_update(i, arr[i]);
    }

    while (1) {
        int choice;
        printf("\n1) Update index\n2) Range sum query\n3) Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        if (choice == 1) {
            size_t idx;
            int val;
            printf("Index and delta: ");
            if (scanf("%zu %d", &idx, &val) != 2 || idx >= n) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            fenwick_update(idx, val);
            arr[idx] += val;
        } else if (choice == 2) {
            size_t l, r;
            printf("Range [l r]: ");
            if (scanf("%zu %zu", &l, &r) != 2 || l > r || r >= n) {
                fprintf(stderr, "Invalid range.\n");
                continue;
            }
            printf("Sum = %d\n", fenwick_range_sum(l, r));
        } else if (choice == 3) {
            break;
        } else {
            fprintf(stderr, "Unknown choice.\n");
        }
    }

    free(arr);
    free(fenwick);
    return 0;
}

