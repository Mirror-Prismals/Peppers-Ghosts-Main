#include <stdio.h>
#include <stdlib.h>

static unsigned long long mod_pow(unsigned long long base,
                                  unsigned long long exp,
                                  unsigned long long mod) {
    unsigned long long result = 1ULL % mod;
    base %= mod;
    while (exp > 0ULL) {
        if (exp & 1ULL) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1ULL;
    }
    return result;
}

static void ntt(unsigned long long *a, int n, unsigned long long root,
                unsigned long long mod) {
    if (n <= 1) {
        return;
    }
    int m = n / 2;
    unsigned long long *even = malloc((size_t)m * sizeof(*even));
    unsigned long long *odd  = malloc((size_t)m * sizeof(*odd));
    if (!even || !odd) {
        perror("malloc");
        free(even); free(odd);
        exit(1);
    }
    for (int i = 0; i < m; ++i) {
        even[i] = a[2 * i];
        odd[i]  = a[2 * i + 1];
    }
    unsigned long long next_root = (root * root) % mod;
    ntt(even, m, next_root, mod);
    ntt(odd, m, next_root, mod);
    unsigned long long w = 1ULL;
    for (int k = 0; k < m; ++k) {
        unsigned long long t = (w * odd[k]) % mod;
        unsigned long long u = even[k];
        a[k] = (u + t) % mod;
        a[k + m] = (u + mod - t) % mod;
        w = (w * root) % mod;
    }
    free(even);
    free(odd);
}

int main(void) {
    int n;
    unsigned long long mod, primitive_root;
    printf("Enter transform length (power of 2): ");
    if (scanf("%d", &n) != 1 || n <= 0 || (n & (n - 1))) {
        fprintf(stderr, "Invalid length.\n");
        return 1;
    }
    printf("Enter prime modulus and primitive root: ");
    if (scanf("%llu %llu", &mod, &primitive_root) != 2 || mod == 0ULL) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    unsigned long long root = mod_pow(primitive_root, (mod - 1ULL) / (unsigned long long)n, mod);
    unsigned long long *data = malloc((size_t)n * sizeof(*data));
    if (!data) {
        perror("malloc");
        return 1;
    }
    printf("Enter %d integers modulo %llu:\n", n, mod);
    for (int i = 0; i < n; ++i) {
        if (scanf("%llu", &data[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(data);
            return 1;
        }
        data[i] %= mod;
    }
    ntt(data, n, root, mod);
    printf("NTT result:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d: %llu\n", i, data[i]);
    }
    free(data);
    return 0;
}
