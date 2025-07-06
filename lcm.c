#include <stdio.h>

static unsigned int gcd(unsigned int a, unsigned int b) {
    while (b != 0u) {
        unsigned int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

static unsigned int lcm(unsigned int a, unsigned int b) {
    if (a == 0u || b == 0u) {
        return 0u;
    }
    return (a / gcd(a, b)) * b;
}

int main(void) {
    unsigned int a, b;
    printf("Enter two non-negative integers: ");
    if (scanf("%u %u", &a, &b) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    printf("lcm(%u, %u) = %u\n", a, b, lcm(a, b));
    return 0;
}
