#include <stdio.h>
#include <stdlib.h>

#define SIZE 9

static int board[SIZE][SIZE];

static int is_safe(int row, int col, int num) {
    for (int i = 0; i < SIZE; ++i) {
        if (board[row][i] == num || board[i][col] == num)
            return 0;
    }
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[start_row + i][start_col + j] == num)
                return 0;
        }
    }
    return 1;
}

static int solve(int row, int col) {
    if (row == SIZE)
        return 1;
    if (board[row][col] != 0) {
        if (col == SIZE - 1)
            return solve(row + 1, 0);
        else
            return solve(row, col + 1);
    }
    for (int num = 1; num <= 9; ++num) {
        if (is_safe(row, col, num)) {
            board[row][col] = num;
            if (col == SIZE - 1) {
                if (solve(row + 1, 0))
                    return 1;
            } else {
                if (solve(row, col + 1))
                    return 1;
            }
            board[row][col] = 0;
        }
    }
    return 0;
}

static void print_board(void) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j)
            printf("%d ", board[i][j]);
        printf("\n");
    }
}

int main(void) {
    char row[16];
    printf("Enter the Sudoku puzzle row by row (9 digits each, 0 for empty):\n");
    for (int i = 0; i < SIZE; ++i) {
        printf("Row %d: ", i + 1);
        if (scanf("%15s", row) != 1) {
            fprintf(stderr, "Invalid input.\n");
            return 1;
        }
        for (int j = 0; j < SIZE; ++j) {
            if (row[j] >= '0' && row[j] <= '9')
                board[i][j] = row[j] - '0';
            else {
                fprintf(stderr, "Invalid character.\n");
                return 1;
            }
        }
    }

    if (solve(0, 0)) {
        printf("Solved Sudoku:\n");
        print_board();
    } else {
        printf("No solution exists.\n");
    }
    return 0;
}

