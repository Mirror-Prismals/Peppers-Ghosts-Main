#include <stdio.h>
#include <stdlib.h>

static double determinant(const double *matrix, int n) {
    if (n == 1) {
        return matrix[0];
    }
    if (n == 2) {
        return matrix[0] * matrix[3] - matrix[1] * matrix[2];
    }
    double det = 0.0;
    double *sub = malloc((size_t)(n - 1) * (n - 1) * sizeof(double));
    if (!sub) {
        perror("malloc");
        exit(1);
    }
    for (int col = 0; col < n; ++col) {
        int subi = 0;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j == col) {
                    continue;
                }
                sub[subi++] = matrix[i * n + j];
            }
        }
        double sub_det = determinant(sub, n - 1);
        double sign = (col % 2 == 0) ? 1.0 : -1.0;
        det += sign * matrix[col] * sub_det;
    }
    free(sub);
    return det;
}

int main(void) {
    int n;
    printf("Enter the dimension of the square matrix: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid dimension.\n");
        return 1;
    }
    double *matrix = malloc((size_t)n * n * sizeof(double));
    if (!matrix) {
        perror("malloc");
        return 1;
    }
    printf("Enter the elements of the %dx%d matrix:\n", n, n);
    for (int i = 0; i < n * n; ++i) {
        if (scanf("%lf", &matrix[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(matrix);
            return 1;
        }
    }
    double det = determinant(matrix, n);
    printf("Determinant: %g\n", det);
    free(matrix);
    return 0;
}
