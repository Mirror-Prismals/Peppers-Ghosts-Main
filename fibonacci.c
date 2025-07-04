#include <stdio.h>

unsigned long long fibonacci(unsigned int n) {
    if (n == 0) return 0ULL;
    if (n == 1) return 1ULL;
    unsigned long long prev = 0ULL, curr = 1ULL, next;
    for (unsigned int i = 2; i <= n; ++i) {
        next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

int main(void) {
    unsigned int count;
    printf("Enter the number of Fibonacci terms (0-93): ");
    if (scanf("%u", &count) != 1 || count > 93) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    for (unsigned int i = 0; i < count; ++i) {
        printf("%u: %llu\n", i, fibonacci(i));
    }
    return 0;
}
