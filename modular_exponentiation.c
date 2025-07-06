#include <stdio.h>

static unsigned long long mod_exp(unsigned long long base,
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

int main(void) {
    unsigned long long base, exp, mod;
    printf("Enter base, exponent, and modulus: ");
    if (scanf("%llu %llu %llu", &base, &exp, &mod) != 3 || mod == 0ULL) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    printf("Result: %llu\n", mod_exp(base, exp, mod));
    return 0;
}
