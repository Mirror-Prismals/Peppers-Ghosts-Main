#include <stdio.h>

unsigned int gcd(unsigned int a, unsigned int b) {
    while (b != 0u) {
        unsigned int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main(void) {
    unsigned int a, b;
    printf("Enter two non-negative integers: ");
    if (scanf("%u %u", &a, &b) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    printf("gcd(%u, %u) = %u\n", a, b, gcd(a, b));
    return 0;
}
