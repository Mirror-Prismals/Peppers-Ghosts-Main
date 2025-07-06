#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

static void fft(complex double *a, int n) {
    if (n <= 1) return;
    int m = n / 2;
    complex double *even = malloc((size_t)m * sizeof(*even));
    complex double *odd  = malloc((size_t)m * sizeof(*odd));
    if (!even || !odd) {
        perror("malloc");
        free(even); free(odd);
        exit(1);
    }
    for (int i = 0; i < m; ++i) {
        even[i] = a[2 * i];
        odd[i]  = a[2 * i + 1];
    }
    fft(even, m);
    fft(odd, m);
    for (int k = 0; k < m; ++k) {
        complex double t = cexp(-2.0 * I * M_PI * k / n) * odd[k];
        a[k] = even[k] + t;
        a[k + m] = even[k] - t;
    }
    free(even);
    free(odd);
}

int main(void) {
    int n;
    printf("Enter number of samples (power of 2): ");
    if (scanf("%d", &n) != 1 || n <= 0 || (n & (n - 1))) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    complex double *data = malloc((size_t)n * sizeof(*data));
    if (!data) {
        perror("malloc");
        return 1;
    }
    printf("Enter %d real values:\n", n);
    for (int i = 0; i < n; ++i) {
        double x;
        if (scanf("%lf", &x) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(data);
            return 1;
        }
        data[i] = x + 0.0 * I;
    }
    fft(data, n);
    printf("FFT result:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d: %f %f\n", i, creal(data[i]), cimag(data[i]));
    }
    free(data);
    return 0;
}
