#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
    unsigned int limit;
    printf("Compute primes up to: ");
    if (scanf("%u", &limit) != 1 || limit < 2) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    char *is_prime = malloc(limit + 1);
    if (!is_prime) {
        perror("malloc");
        return 1;
    }
    for (unsigned int i = 2; i <= limit; ++i) {
        is_prime[i] = 1;
    }
    for (unsigned int p = 2; p * p <= limit; ++p) {
        if (is_prime[p]) {
            for (unsigned int multiple = p * p; multiple <= limit; multiple += p) {
                is_prime[multiple] = 0;
            }
        }
    }
    printf("Primes up to %u:\n", limit);
    for (unsigned int i = 2; i <= limit; ++i) {
        if (is_prime[i]) {
            printf("%u\n", i);
        }
    }
    free(is_prime);
    return 0;
}
