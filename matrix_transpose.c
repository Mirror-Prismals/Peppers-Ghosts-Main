#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int rows, cols;
    printf("Enter rows and columns of the matrix: ");
    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0) {
        fprintf(stderr, "Invalid dimensions.\n");
        return 1;
    }

    double *matrix = malloc((size_t)rows * cols * sizeof(double));
    if (!matrix) {
        perror("malloc");
        return 1;
    }

    printf("Enter elements (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows * cols; ++i) {
        if (scanf("%lf", &matrix[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(matrix);
            return 1;
        }
    }

    printf("Original matrix:\n");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%g ", matrix[i * cols + j]);
        }
        putchar('\n');
    }

    printf("\nTransposed matrix:\n");
    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            printf("%g ", matrix[i * cols + j]);
        }
        putchar('\n');
    }

    free(matrix);
    return 0;
}
