#include <stdio.h>
#include <stdint.h>

static unsigned long long mod_mul(unsigned long long a,
                                  unsigned long long b,
                                  unsigned long long mod) {
    return (unsigned long long)((__uint128_t)a * b % mod);
}

static unsigned long long mod_pow(unsigned long long base,
                                  unsigned long long exp,
                                  unsigned long long mod) {
    unsigned long long result = 1ULL % mod;
    base %= mod;
    while (exp > 0ULL) {
        if (exp & 1ULL) {
            result = mod_mul(result, base, mod);
        }
        base = mod_mul(base, base, mod);
        exp >>= 1ULL;
    }
    return result;
}

static int is_probable_prime(unsigned long long n) {
    if (n < 2ULL) {
        return 0;
    }
    static const unsigned long long bases[] = {
        2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL
    };
    for (size_t i = 0; i < sizeof(bases) / sizeof(bases[0]); ++i) {
        if (n % bases[i] == 0ULL) {
            return n == bases[i];
        }
    }
    unsigned long long d = n - 1ULL;
    unsigned int s = 0U;
    while ((d & 1ULL) == 0ULL) {
        d >>= 1ULL;
        ++s;
    }
    for (size_t i = 0; i < sizeof(bases) / sizeof(bases[0]); ++i) {
        unsigned long long a = bases[i];
        if (a >= n) {
            continue;
        }
        unsigned long long x = mod_pow(a, d, n);
        if (x == 1ULL || x == n - 1ULL) {
            continue;
        }
        int r;
        for (r = 1; r < (int)s; ++r) {
            x = mod_mul(x, x, n);
            if (x == n - 1ULL) {
                break;
            }
        }
        if (r == (int)s) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    unsigned long long n;
    printf("Enter an integer to test for primality: ");
    if (scanf("%llu", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    if (is_probable_prime(n)) {
        printf("%llu is probably prime.\n", n);
    } else {
        printf("%llu is composite.\n", n);
    }
    return 0;
}
