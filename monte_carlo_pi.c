#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    unsigned long long trials;
    printf("Enter number of trials: ");
    if (scanf("%llu", &trials) != 1 || trials == 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    srand((unsigned)time(NULL));
    unsigned long long inside = 0;
    for (unsigned long long i = 0; i < trials; ++i) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (x*x + y*y <= 1.0) {
            ++inside;
        }
    }
    double pi_estimate = 4.0 * inside / trials;
    printf("Estimated pi: %f\n", pi_estimate);
    return 0;
}
