#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int r1, c1, r2, c2;
    printf("Enter rows and columns of first matrix: ");
    if (scanf("%d %d", &r1, &c1) != 2 || r1 <= 0 || c1 <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    printf("Enter rows and columns of second matrix: ");
    if (scanf("%d %d", &r2, &c2) != 2 || r2 <= 0 || c2 <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    if (c1 != r2) {
        fprintf(stderr, "Incompatible matrix dimensions.\n");
        return 1;
    }

    double *A = malloc((size_t)r1 * c1 * sizeof(double));
    double *B = malloc((size_t)r2 * c2 * sizeof(double));
    double *C = calloc((size_t)r1 * c2, sizeof(double));
    if (!A || !B || !C) {
        perror("malloc");
        free(A);
        free(B);
        free(C);
        return 1;
    }

    printf("Enter elements of first matrix (%d x %d):\n", r1, c1);
    for (int i = 0; i < r1 * c1; ++i) {
        if (scanf("%lf", &A[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(A); free(B); free(C);
            return 1;
        }
    }
    printf("Enter elements of second matrix (%d x %d):\n", r2, c2);
    for (int i = 0; i < r2 * c2; ++i) {
        if (scanf("%lf", &B[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(A); free(B); free(C);
            return 1;
        }
    }

    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c2; ++j) {
            double sum = 0.0;
            for (int k = 0; k < c1; ++k) {
                sum += A[i * c1 + k] * B[k * c2 + j];
            }
            C[i * c2 + j] = sum;
        }
    }

    printf("Result matrix (%d x %d):\n", r1, c2);
    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c2; ++j) {
            printf("%g ", C[i * c2 + j]);
        }
        putchar('\n');
    }

    free(A);
    free(B);
    free(C);
    return 0;
}
