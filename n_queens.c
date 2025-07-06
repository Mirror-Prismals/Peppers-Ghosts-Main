#include <stdio.h>
#include <stdlib.h>

static int n;
static int *columns;
static int *diag1;
static int *diag2;
static int *board;
static unsigned long solutions = 0;

void solve(int row) {
    if (row == n) {
        ++solutions;
        printf("Solution %lu:\n", solutions);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i] == j)
                    printf("Q ");
                else
                    printf(". ");
            }
            printf("\n");
        }
        printf("\n");
        return;
    }
    for (int col = 0; col < n; ++col) {
        if (!columns[col] && !diag1[row + col] && !diag2[row - col + n - 1]) {
            board[row] = col;
            columns[col] = diag1[row + col] = diag2[row - col + n - 1] = 1;
            solve(row + 1);
            columns[col] = diag1[row + col] = diag2[row - col + n - 1] = 0;
        }
    }
}

int main(void) {
    printf("Enter board size N (1-12): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 12) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    columns = calloc(n, sizeof(int));
    diag1 = calloc(2 * n, sizeof(int));
    diag2 = calloc(2 * n, sizeof(int));
    board = calloc(n, sizeof(int));

    if (!columns || !diag1 || !diag2 || !board) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(columns);
        free(diag1);
        free(diag2);
        free(board);
        return 1;
    }

    solve(0);
    printf("Total solutions: %lu\n", solutions);

    free(columns);
    free(diag1);
    free(diag2);
    free(board);
    return 0;
}
