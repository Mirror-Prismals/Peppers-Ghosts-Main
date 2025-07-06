#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, capacity;
    printf("Enter number of items: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    printf("Enter knapsack capacity: ");
    if (scanf("%d", &capacity) != 1 || capacity < 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    int *weight = malloc(n * sizeof(int));
    int *value = malloc(n * sizeof(int));
    if (!weight || !value) {
        perror("malloc");
        free(weight);
        free(value);
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        printf("Enter weight and value of item %d: ", i + 1);
        if (scanf("%d %d", &weight[i], &value[i]) != 2 ||
            weight[i] < 0 || value[i] < 0) {
            fprintf(stderr, "Invalid input.\n");
            free(weight);
            free(value);
            return 1;
        }
    }

    int *dp = calloc((n + 1) * (capacity + 1), sizeof(int));
    int *keep = calloc((n + 1) * (capacity + 1), sizeof(int));
    if (!dp || !keep) {
        perror("calloc");
        free(weight);
        free(value);
        free(dp);
        free(keep);
        return 1;
    }

    #define DP(i, w) dp[(i) * (capacity + 1) + (w)]
    #define KEEP(i, w) keep[(i) * (capacity + 1) + (w)]

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (weight[i - 1] <= w) {
                int val = value[i - 1] + DP(i - 1, w - weight[i - 1]);
                if (val > DP(i - 1, w)) {
                    DP(i, w) = val;
                    KEEP(i, w) = 1;
                } else {
                    DP(i, w) = DP(i - 1, w);
                }
            } else {
                DP(i, w) = DP(i - 1, w);
            }
        }
    }

    printf("Maximum value: %d\n", DP(n, capacity));
    printf("Items included:");
    int w = capacity;
    for (int i = n; i >= 1; --i) {
        if (KEEP(i, w)) {
            printf(" %d", i);
            w -= weight[i - 1];
        }
    }
    printf("\n");

    free(weight);
    free(value);
    free(dp);
    free(keep);
    return 0;
}

