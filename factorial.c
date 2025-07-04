#include <stdio.h>

unsigned long long factorial(unsigned int n) {
    unsigned long long result = 1ULL;
    for (unsigned int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int main(void) {
    unsigned int n;
    printf("Enter a non-negative integer (0-20): ");
    if (scanf("%u", &n) != 1 || n > 20) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    printf("%u! = %llu\n", n, factorial(n));
    return 0;
}
