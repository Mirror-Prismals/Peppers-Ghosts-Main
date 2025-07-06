#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    int *dp = calloc((len1 + 1) * (len2 + 1), sizeof(int));
    if (!dp) {
        perror("calloc");
        return 1;
    }

    #define DP(i, j) dp[(i) * (len2 + 1) + (j)]

    int max_len = 0;
    size_t end_i = 0;

    for (size_t i = 1; i <= len1; ++i) {
        for (size_t j = 1; j <= len2; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                DP(i, j) = DP(i - 1, j - 1) + 1;
                if (DP(i, j) > max_len) {
                    max_len = DP(i, j);
                    end_i = i;
                }
            } else {
                DP(i, j) = 0;
            }
        }
    }

    char *lcs = malloc((size_t)max_len + 1);
    if (!lcs) {
        perror("malloc");
        free(dp);
        return 1;
    }
    if (max_len > 0) {
        memcpy(lcs, &s1[end_i - max_len], (size_t)max_len);
    }
    lcs[max_len] = '\0';

    printf("Length of longest common substring: %d\n", max_len);
    printf("Longest common substring: %s\n", lcs);

    free(lcs);
    free(dp);
    return 0;
}
