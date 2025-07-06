#include <stdio.h>

static unsigned int binary_gcd(unsigned int a, unsigned int b) {
    if (a == 0u) return b;
    if (b == 0u) return a;

    int shift = 0;
    while (((a | b) & 1u) == 0u) {
        a >>= 1;
        b >>= 1;
        ++shift;
    }
    while ((a & 1u) == 0u) {
        a >>= 1;
    }
    do {
        while ((b & 1u) == 0u) {
            b >>= 1;
        }
        if (a > b) {
            unsigned int t = a;
            a = b;
            b = t;
        }
        b = b - a;
    } while (b != 0u);

    return a << shift;
}

int main(void) {
    unsigned int a, b;
    printf("Enter two non-negative integers: ");
    if (scanf("%u %u", &a, &b) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    printf("binary_gcd(%u, %u) = %u\n", a, b, binary_gcd(a, b));
    return 0;
}
