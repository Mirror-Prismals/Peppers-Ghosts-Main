#include <stdio.h>
#include <stdlib.h>

static void spiral_print(int **matrix, int rows, int cols) {
    int top = 0, bottom = rows - 1;
    int left = 0, right = cols - 1;

    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; ++j) {
            printf("%d ", matrix[top][j]);
        }
        top++;

        for (int i = top; i <= bottom; ++i) {
            printf("%d ", matrix[i][right]);
        }
        right--;

        if (top <= bottom) {
            for (int j = right; j >= left; --j) {
                printf("%d ", matrix[bottom][j]);
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; --i) {
                printf("%d ", matrix[i][left]);
            }
            left++;
        }
    }
    putchar('\n');
}

int main(void) {
    int rows, cols;
    printf("Enter matrix dimensions (rows cols): ");
    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0) {
        fprintf(stderr, "Invalid dimensions.\n");
        return 1;
    }

    int **matrix = malloc((size_t)rows * sizeof(*matrix));
    if (!matrix) {
        perror("malloc");
        return 1;
    }
    for (int i = 0; i < rows; ++i) {
        matrix[i] = malloc((size_t)cols * sizeof(**matrix));
        if (!matrix[i]) {
            perror("malloc");
            for (int j = 0; j < i; ++j) {
                free(matrix[j]);
            }
            free(matrix);
            return 1;
        }
    }

    printf("Enter %d elements:\n", rows * cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                fprintf(stderr, "Invalid input.\n");
                for (int r = 0; r < rows; ++r) {
                    free(matrix[r]);
                }
                free(matrix);
                return 1;
            }
        }
    }

    printf("Spiral order:\n");
    spiral_print(matrix, rows, cols);

    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}
