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

    char *is_prime = calloc(limit + 1, sizeof(char));
    if (!is_prime) {
        perror("calloc");
        return 1;
    }

    unsigned int sqrt_limit = (unsigned int)sqrt((double)limit);
    for (unsigned int x = 1; x <= sqrt_limit; ++x) {
        for (unsigned int y = 1; y <= sqrt_limit; ++y) {
            unsigned int n = 4 * x * x + y * y;
            if (n <= limit && (n % 12 == 1 || n % 12 == 5)) {
                is_prime[n] ^= 1;
            }
            n = 3 * x * x + y * y;
            if (n <= limit && n % 12 == 7) {
                is_prime[n] ^= 1;
            }
            if (x > y) {
                n = 3 * x * x - y * y;
                if (n <= limit && n % 12 == 11) {
                    is_prime[n] ^= 1;
                }
            }
        }
    }

    for (unsigned int i = 5; i <= sqrt_limit; ++i) {
        if (is_prime[i]) {
            unsigned int k = i * i;
            for (unsigned int j = k; j <= limit; j += k) {
                is_prime[j] = 0;
            }
        }
    }

    printf("Primes up to %u:\n", limit);
    if (limit >= 2) {
        printf("2\n");
    }
    if (limit >= 3) {
        printf("3\n");
    }
    for (unsigned int n = 5; n <= limit; n += 2) {
        if (is_prime[n]) {
            printf("%u\n", n);
        }
    }

    free(is_prime);
    return 0;
}
