#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void compute_z(const char *s, size_t n, int *z) {
    z[0] = (int)n;
    size_t l = 0, r = 0;
    for (size_t i = 1; i < n; ++i) {
        if (i <= r) {
            size_t k = i - l;
            z[i] = (int)((r - i + 1) < (size_t)z[k] ? (r - i + 1) : (size_t)z[k]);
        } else {
            z[i] = 0;
        }
        while (i + (size_t)z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + (size_t)z[i] - 1 > r) {
            l = i;
            r = i + (size_t)z[i] - 1;
        }
    }
}

static int z_search(const char *text, const char *pattern) {
    size_t n = strlen(text);
    size_t m = strlen(pattern);
    if (m == 0) {
        return 0;
    }

    size_t len = m + 1 + n;
    char *s = malloc(len + 1); // include delimiter
    if (!s) {
        perror("malloc");
        exit(1);
    }
    memcpy(s, pattern, m);
    s[m] = '\1'; // delimiter unlikely to appear in text or pattern
    memcpy(s + m + 1, text, n);
    s[len] = '\0';

    int *z = malloc(len * sizeof(int));
    if (!z) {
        perror("malloc");
        free(s);
        exit(1);
    }

    compute_z(s, len, z);
    for (size_t i = m + 1; i < len; ++i) {
        if (z[i] == (int)m) {
            free(z);
            free(s);
            return (int)(i - m - 1);
        }
    }
    free(z);
    free(s);
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

    int idx = z_search(text, pattern);
    if (idx >= 0) {
        printf("Pattern found at index %d\n", idx);
    } else {
        printf("Pattern not found\n");
    }
    return 0;
}

