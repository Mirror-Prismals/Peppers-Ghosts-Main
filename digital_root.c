#include <stdio.h>

unsigned int digital_root(unsigned int n) {
    while (n >= 10u) {
        unsigned int sum = 0u;
        while (n > 0u) {
            sum += n % 10u;
            n /= 10u;
        }
        n = sum;
    }
    return n;
}

int main(void) {
    unsigned int n;
    printf("Enter a non-negative integer: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    printf("Digital root: %u\n", digital_root(n));
    return 0;
}
