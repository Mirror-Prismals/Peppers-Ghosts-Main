#include <stdio.h>

int main(void) {
    unsigned long long n;
    printf("Enter a positive integer: ");
    if (scanf("%llu", &n) != 1 || n == 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    unsigned int steps = 0;
    printf("%u: %llu\n", steps, n);
    while (n != 1) {
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
        ++steps;
        printf("%u: %llu\n", steps, n);
    }
    printf("Total steps: %u\n", steps);
    return 0;
}
