#include <stdio.h>
#include <stdlib.h>

static unsigned long long catalan(unsigned int n) {
    unsigned long long *dp = malloc((n + 1) * sizeof(*dp));
    if (!dp) {
        return 0ULL;
    }
    dp[0] = 1ULL;
    for (unsigned int i = 1; i <= n; ++i) {
        dp[i] = 0ULL;
        for (unsigned int j = 0; j < i; ++j) {
            dp[i] += dp[j] * dp[i - 1 - j];
        }
    }
    unsigned long long result = dp[n];
    free(dp);
    return result;
}

int main(void) {
    unsigned int n;
    printf("Enter n (0-36): ");
    if (scanf("%u", &n) != 1 || n > 36) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    unsigned long long result = catalan(n);
    if (result == 0ULL && n != 0) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    printf("Catalan(%u) = %llu\n", n, result);
    return 0;
}
