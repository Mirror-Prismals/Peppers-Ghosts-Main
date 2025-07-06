#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    printf("Enter number of items: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    int *weights = malloc(n * sizeof(int));
    int *values = malloc(n * sizeof(int));
    if (!weights || !values) {
        perror("malloc");
        free(weights);
        free(values);
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        printf("Enter weight and value for item %d: ", i + 1);
        if (scanf("%d %d", &weights[i], &values[i]) != 2 ||
            weights[i] <= 0 || values[i] < 0) {
            fprintf(stderr, "Invalid input.\n");
            free(weights);
            free(values);
            return 1;
        }
    }

    int capacity;
    printf("Enter knapsack capacity: ");
    if (scanf("%d", &capacity) != 1 || capacity < 0) {
        fprintf(stderr, "Invalid input.\n");
        free(weights);
        free(values);
        return 1;
    }

    int *dp = calloc((n + 1) * (capacity + 1), sizeof(int));
    if (!dp) {
        perror("calloc");
        free(weights);
        free(values);
        return 1;
    }

#define DP(i, w) dp[(i) * (capacity + 1) + (w)]
    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            int wi = weights[i - 1];
            int vi = values[i - 1];
            if (wi > w) {
                DP(i, w) = DP(i - 1, w);
            } else {
                int without = DP(i - 1, w);
                int with = DP(i - 1, w - wi) + vi;
                DP(i, w) = (with > without) ? with : without;
            }
        }
    }

    printf("Maximum value: %d\n", DP(n, capacity));

    printf("Items included (1-based indices):");
    int w = capacity;
    for (int i = n; i >= 1; --i) {
        if (DP(i, w) != DP(i - 1, w)) {
            printf(" %d", i);
            w -= weights[i - 1];
        }
    }
    printf("\n");

    free(dp);
    free(weights);
    free(values);
    return 0;
}
