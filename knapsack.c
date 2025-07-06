#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    printf("Enter number of items: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    int capacity;
    printf("Enter knapsack capacity: ");
    if (scanf("%d", &capacity) != 1 || capacity <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    int *weights = malloc((size_t)n * sizeof(int));
    int *values = malloc((size_t)n * sizeof(int));
    if (!weights || !values) {
        perror("malloc");
        free(weights);
        free(values);
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        printf("Item %d weight and value: ", i + 1);
        if (scanf("%d %d", &weights[i], &values[i]) != 2 || weights[i] < 0 || values[i] < 0) {
            fprintf(stderr, "Invalid input.\n");
            free(weights);
            free(values);
            return 1;
        }
    }

    int *dp = calloc((size_t)capacity + 1, sizeof(int));
    if (!dp) {
        perror("calloc");
        free(weights);
        free(values);
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        for (int w = capacity; w >= weights[i]; --w) {
            int val = dp[w - weights[i]] + values[i];
            if (val > dp[w]) {
                dp[w] = val;
            }
        }
    }

    printf("Maximum value: %d\n", dp[capacity]);

    free(dp);
    free(weights);
    free(values);
    return 0;
}
