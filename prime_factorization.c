#include <stdio.h>
#include <stdlib.h>

int main(void) {
    unsigned long long n;
    printf("Enter a positive integer: ");
    if (scanf("%llu", &n) != 1 || n < 2) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    printf("Prime factors of %llu:\n", n);
    unsigned long long divisor = 2;
    while (n > 1 && divisor * divisor <= n) {
        while (n % divisor == 0) {
            printf("%llu\n", divisor);
            n /= divisor;
        }
        ++divisor;
    }
    if (n > 1) {
        printf("%llu\n", n);
    }
    return 0;
}
