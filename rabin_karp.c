#include <stdio.h>
#include <string.h>

#define BASE 256
#define PRIME 101

static int rabin_karp_search(const char *text, const char *pattern) {
    size_t n = strlen(text);
    size_t m = strlen(pattern);
    if (m == 0) {
        return 0;
    }
    if (m > n) {
        return -1;
    }

    int h = 1;
    for (size_t i = 0; i < m - 1; ++i) {
        h = (h * BASE) % PRIME;
    }

    int p = 0; // hash value for pattern
    int t = 0; // hash value for text

    for (size_t i = 0; i < m; ++i) {
        p = (BASE * p + (unsigned char)pattern[i]) % PRIME;
        t = (BASE * t + (unsigned char)text[i]) % PRIME;
    }

    for (size_t i = 0; i <= n - m; ++i) {
        if (p == t) {
            if (strncmp(text + i, pattern, m) == 0) {
                return (int)i;
            }
        }
        if (i < n - m) {
            t = (BASE * (t - (unsigned char)text[i] * h) + (unsigned char)text[i + m]) % PRIME;
            if (t < 0) {
                t += PRIME;
            }
        }
    }
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

    int idx = rabin_karp_search(text, pattern);
    if (idx >= 0) {
        printf("Pattern found at index %d\n", idx);
    } else {
        printf("Pattern not found\n");
    }
    return 0;
}
