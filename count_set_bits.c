#include <stdio.h>

unsigned int count_set_bits(unsigned int n) {
    unsigned int count = 0u;
    while (n != 0u) {
        n &= n - 1u;
        ++count;
    }
    return count;
}

int main(void) {
    unsigned int n;
    printf("Enter a non-negative integer: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    printf("Number of set bits in %u: %u\n", n, count_set_bits(n));
    return 0;
}
