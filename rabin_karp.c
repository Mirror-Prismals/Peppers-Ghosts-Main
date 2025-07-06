#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int rabin_karp_search(const char *text, const char *pattern) {
    const int d = 256;          // number of characters in input alphabet
    const int q = 101;          // a prime number for modulus

    size_t n = strlen(text);
    size_t m = strlen(pattern);
    if (m == 0) {
        return 0;
    }
    if (n < m) {
        return -1;
    }

    int h = 1;
    for (size_t i = 0; i < m - 1; ++i) {
        h = (h * d) % q;
    }

    int p = 0; // hash value for pattern
    int t = 0; // hash value for text window
    for (size_t i = 0; i < m; ++i) {
        p = (d * p + (unsigned char)pattern[i]) % q;
        t = (d * t + (unsigned char)text[i]) % q;
    }

    for (size_t i = 0; i <= n - m; ++i) {
        if (p == t) {
            int match = 1;
            for (size_t j = 0; j < m; ++j) {
                if (text[i + j] != pattern[j]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                return (int)i;
            }
        }
        if (i < n - m) {
            t = (d * (t - (unsigned char)text[i] * h) + (unsigned char)text[i + m]) % q;
            if (t < 0) {
                t += q;
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

