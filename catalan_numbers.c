#include <stdio.h>
#include <stdlib.h>

static unsigned long long catalan(unsigned int n) {
    unsigned long long *c = malloc((n + 1) * sizeof(*c));
    if (!c) {
        perror("malloc");
        exit(1);
    }
    c[0] = 1ULL;
    for (unsigned int i = 1; i <= n; ++i) {
        c[i] = 0ULL;
        for (unsigned int j = 0; j < i; ++j) {
            c[i] += c[j] * c[i - 1 - j];
        }
    }
    unsigned long long result = c[n];
    free(c);
    return result;
}

int main(void) {
    unsigned int n;
    printf("Enter n (0-36): ");
    if (scanf("%u", &n) != 1 || n > 36) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    printf("Catalan(%u) = %llu\n", n, catalan(n));
    return 0;
}
