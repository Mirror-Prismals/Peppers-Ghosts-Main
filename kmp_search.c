#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int kmp_search(const char *text, const char *pattern) {
    size_t n = strlen(text);
    size_t m = strlen(pattern);
    if (m == 0) {
        return 0;
    }
    int *pi = malloc(m * sizeof(int));
    if (!pi) {
        perror("malloc");
        exit(1);
    }
    pi[0] = 0;
    for (size_t i = 1; i < m; ++i) {
        int j = pi[i - 1];
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            ++j;
        }
        pi[i] = j;
    }
    int j = 0;
    for (size_t i = 0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (text[i] == pattern[j]) {
            ++j;
            if ((size_t)j == m) {
                free(pi);
                return (int)(i - m + 1);
            }
        }
    }
    free(pi);
    return -1;
}

int main(void) {
    char text[1024];
    char pattern[256];

    printf("Enter text: ");
    if (!fgets(text, sizeof(text), stdin)) {
        return 1;
    }
    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[--len] = '\0';
    }

    printf("Enter pattern: ");
    if (!fgets(pattern, sizeof(pattern), stdin)) {
        return 1;
    }
    len = strlen(pattern);
    if (len > 0 && pattern[len - 1] == '\n') {
        pattern[--len] = '\0';
    }

    int idx = kmp_search(text, pattern);
    if (idx >= 0) {
        printf("Pattern found at index %d\n", idx);
    } else {
        printf("Pattern not found\n");
    }
    return 0;
}

