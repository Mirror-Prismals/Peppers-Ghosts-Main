#include <stdio.h>
#include <stdlib.h>

static int max(int a, int b) { return a > b ? a : b; }

int main(void) {
    int n;
    printf("Enter number of integers: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    int *arr = malloc((size_t)n * sizeof(int));
    if (!arr) {
        perror("malloc");
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(arr);
            return 1;
        }
    }

    int *dp = malloc((size_t)n * sizeof(int));
    if (!dp) {
        perror("malloc");
        free(arr);
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        dp[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (arr[i] > arr[j])
                dp[i] = max(dp[i], dp[j] + 1);
        }
    }

    int lis = 0;
    for (int i = 0; i < n; ++i) {
        lis = max(lis, dp[i]);
    }

    printf("Length of LIS: %d\n", lis);

    free(dp);
    free(arr);
    return 0;
}
