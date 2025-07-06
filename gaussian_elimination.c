#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static void swap_rows(double *a, int n, int r1, int r2) {
    if (r1 == r2) return;
    for (int j = 0; j <= n; ++j) {
        double tmp = a[r1*(n+1)+j];
        a[r1*(n+1)+j] = a[r2*(n+1)+j];
        a[r2*(n+1)+j] = tmp;
    }
}

int main(void) {
    int n;
    printf("Enter matrix size (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid size.\n");
        return 1;
    }

    double *a = malloc((size_t)n * (n + 1) * sizeof(double));
    if (!a) {
        perror("malloc");
        return 1;
    }

    printf("Enter augmented matrix (%d rows, %d columns):\n", n, n + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (scanf("%lf", &a[i*(n+1)+j]) != 1) {
                fprintf(stderr, "Invalid input.\n");
                free(a);
                return 1;
            }
        }
    }

    // Forward elimination with partial pivoting
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        double max = fabs(a[i*(n+1)+i]);
        for (int r = i + 1; r < n; ++r) {
            double val = fabs(a[r*(n+1)+i]);
            if (val > max) {
                max = val;
                pivot = r;
            }
        }
        if (max == 0.0) {
            fprintf(stderr, "Matrix is singular.\n");
            free(a);
            return 1;
        }
        swap_rows(a, n, i, pivot);
        for (int r = i + 1; r < n; ++r) {
            double factor = a[r*(n+1)+i] / a[i*(n+1)+i];
            for (int c = i; c <= n; ++c) {
                a[r*(n+1)+c] -= factor * a[i*(n+1)+c];
            }
        }
    }

    double *x = calloc((size_t)n, sizeof(double));
    if (!x) {
        perror("calloc");
        free(a);
        return 1;
    }

    // Back substitution
    for (int i = n - 1; i >= 0; --i) {
        double sum = a[i*(n+1)+n];
        for (int j = i + 1; j < n; ++j) {
            sum -= a[i*(n+1)+j] * x[j];
        }
        x[i] = sum / a[i*(n+1)+i];
    }

    printf("Solution:\n");
    for (int i = 0; i < n; ++i) {
        printf("x%d = %.6f\n", i + 1, x[i]);
    }

    free(a);
    free(x);
    return 0;
}

