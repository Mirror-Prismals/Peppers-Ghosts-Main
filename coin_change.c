#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    printf("Enter number of coin denominations: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    int *coins = malloc(n * sizeof(int));
    if (!coins) {
        perror("malloc");
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        printf("Enter value for coin %d: ", i + 1);
        if (scanf("%d", &coins[i]) != 1 || coins[i] <= 0) {
            fprintf(stderr, "Invalid input.\n");
            free(coins);
            return 1;
        }
    }

    int amount;
    printf("Enter target amount: ");
    if (scanf("%d", &amount) != 1 || amount < 0) {
        fprintf(stderr, "Invalid input.\n");
        free(coins);
        return 1;
    }

    int *dp = malloc((amount + 1) * sizeof(int));
    int *prev = malloc((amount + 1) * sizeof(int));
    if (!dp || !prev) {
        perror("malloc");
        free(dp);
        free(prev);
        free(coins);
        return 1;
    }

    dp[0] = 0;
    prev[0] = -1;
    for (int i = 1; i <= amount; ++i) {
        dp[i] = amount + 1;
        prev[i] = -1;
    }

    for (int i = 1; i <= amount; ++i) {
        for (int j = 0; j < n; ++j) {
            int c = coins[j];
            if (c <= i && dp[i - c] + 1 < dp[i]) {
                dp[i] = dp[i - c] + 1;
                prev[i] = j;
            }
        }
    }

    if (dp[amount] == amount + 1) {
        printf("No solution to make amount %d with given coins.\n", amount);
    } else {
        printf("Minimum coins required: %d\n", dp[amount]);
        printf("Coins used:");
        int a = amount;
        while (a > 0) {
            int j = prev[a];
            if (j < 0) break;
            printf(" %d", coins[j]);
            a -= coins[j];
        }
        printf("\n");
    }

    free(dp);
    free(prev);
    free(coins);
    return 0;
}

