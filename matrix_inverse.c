#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * Compute the inverse of an n x n matrix using Gauss-Jordan elimination.
 * Returns 0 on success and -1 if the matrix is singular.
 */

static int invert_matrix(double **aug, int n) {
    for (int i = 0; i < n; ++i) {
        /* Find pivot */
        int pivot = i;
        for (int row = i + 1; row < n; ++row) {
            if (fabs(aug[row][i]) > fabs(aug[pivot][i])) {
                pivot = row;
            }
        }
        if (fabs(aug[pivot][i]) < 1e-12) {
            return -1; /* Singular matrix */
        }
        if (pivot != i) {
            /* Swap rows */
            double *tmp = aug[i];
            aug[i] = aug[pivot];
            aug[pivot] = tmp;
        }
        /* Normalize pivot row */
        double div = aug[i][i];
        for (int j = 0; j < 2 * n; ++j) {
            aug[i][j] /= div;
        }
        /* Eliminate other rows */
        for (int k = 0; k < n; ++k) {
            if (k == i) continue;
            double factor = aug[k][i];
            for (int j = 0; j < 2 * n; ++j) {
                aug[k][j] -= factor * aug[i][j];
            }
        }
    }
    return 0;
}

int main(void) {
    int n;
    printf("Enter matrix dimension: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid dimension.\n");
        return 1;
    }

    double **aug = malloc((size_t)n * sizeof(*aug));
    if (!aug) {
        perror("malloc");
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        aug[i] = calloc((size_t)2 * n, sizeof(double));
        if (!aug[i]) {
            perror("calloc");
            for (int j = 0; j < i; ++j) free(aug[j]);
            free(aug);
            return 1;
        }
    }

    printf("Enter elements of the %dx%d matrix:\n", n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (scanf("%lf", &aug[i][j]) != 1) {
                fprintf(stderr, "Invalid input.\n");
                for (int k = 0; k < n; ++k) free(aug[k]);
                free(aug);
                return 1;
            }
        }
        aug[i][n + i] = 1.0; /* identity matrix */
    }

    if (invert_matrix(aug, n) != 0) {
        fprintf(stderr, "Matrix is singular.\n");
        for (int i = 0; i < n; ++i) free(aug[i]);
        free(aug);
        return 1;
    }

    printf("Inverse matrix:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%g ", aug[i][n + j]);
        }
        putchar('\n');
    }

    for (int i = 0; i < n; ++i) free(aug[i]);
    free(aug);
    return 0;
}
