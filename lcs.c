#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int max(int a, int b) {
    return a > b ? a : b;
}

int main(void) {
    char s1[1024];
    char s2[1024];

    printf("Enter first string: ");
    if (!fgets(s1, sizeof(s1), stdin)) {
        return 1;
    }
    size_t len1 = strlen(s1);
    if (len1 > 0 && s1[len1 - 1] == '\n') {
        s1[--len1] = '\0';
    }

    printf("Enter second string: ");
    if (!fgets(s2, sizeof(s2), stdin)) {
        return 1;
    }
    size_t len2 = strlen(s2);
    if (len2 > 0 && s2[len2 - 1] == '\n') {
        s2[--len2] = '\0';
    }

    int *dp = malloc((len1 + 1) * (len2 + 1) * sizeof(int));
    if (!dp) {
        perror("malloc");
        return 1;
    }

#define DP(i, j) dp[(i) * (len2 + 1) + (j)]

    for (size_t i = 0; i <= len1; ++i) {
        for (size_t j = 0; j <= len2; ++j) {
            if (i == 0 || j == 0) {
                DP(i, j) = 0;
            } else if (s1[i - 1] == s2[j - 1]) {
                DP(i, j) = DP(i - 1, j - 1) + 1;
            } else {
                DP(i, j) = max(DP(i - 1, j), DP(i, j - 1));
            }
        }
    }

    int lcs_length = DP(len1, len2);
    char *lcs = malloc(lcs_length + 1);
    if (!lcs) {
        perror("malloc");
        free(dp);
        return 1;
    }
    lcs[lcs_length] = '\0';

    size_t i = len1;
    size_t j = len2;
    int index = lcs_length - 1;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs[index--] = s1[i - 1];
            --i;
            --j;
        } else if (DP(i - 1, j) >= DP(i, j - 1)) {
            --i;
        } else {
            --j;
        }
    }

    printf("Length of LCS: %d\n", lcs_length);
    if (lcs_length > 0) {
        printf("LCS: %s\n", lcs);
    }

    free(lcs);
    free(dp);
    return 0;
}

