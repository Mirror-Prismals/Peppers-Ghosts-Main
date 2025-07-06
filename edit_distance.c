#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int min3(int a, int b, int c) {
    if (a <= b && a <= c) return a;
    if (b <= c) return b;
    return c;
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
        DP(i, 0) = (int)i;
    }
    for (size_t j = 0; j <= len2; ++j) {
        DP(0, j) = (int)j;
    }

    for (size_t i = 1; i <= len1; ++i) {
        for (size_t j = 1; j <= len2; ++j) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            DP(i, j) = min3(DP(i - 1, j) + 1,
                             DP(i, j - 1) + 1,
                             DP(i - 1, j - 1) + cost);
        }
    }

    printf("Edit distance: %d\n", DP(len1, len2));

    free(dp);
    return 0;
}

