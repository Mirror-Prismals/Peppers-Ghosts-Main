#include <stdio.h>

static unsigned long long fast_pow(unsigned long long base, unsigned long long exp) {
    unsigned long long result = 1ULL;
    while (exp > 0ULL) {
        if (exp & 1ULL) {
            result *= base;
        }
        base *= base;
        exp >>= 1ULL;
    }
    return result;
}

int main(void) {
    unsigned long long base, exponent;
    printf("Enter base and exponent: ");
    if (scanf("%llu %llu", &base, &exponent) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    printf("%llu^%llu = %llu\n", base, exponent, fast_pow(base, exponent));
    return 0;
}
