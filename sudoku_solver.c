#include <stdio.h>

#define SIZE 9

static int board[SIZE][SIZE];

static void print_board(void) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            printf("%d ", board[i][j]);
        }
        putchar('\n');
    }
}

static int is_valid(int row, int col, int num) {
    for (int i = 0; i < SIZE; ++i) {
        if (board[row][i] == num || board[i][col] == num)
            return 0;
    }
    int start_row = (row / 3) * 3;
    int start_col = (col / 3) * 3;
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
    if (col == SIZE)
        return solve(row + 1, 0);
    if (board[row][col] != 0)
        return solve(row, col + 1);
    for (int num = 1; num <= 9; ++num) {
        if (is_valid(row, col, num)) {
            board[row][col] = num;
            if (solve(row, col + 1))
                return 1;
            board[row][col] = 0;
        }
    }
    return 0;
}

int main(void) {
    printf("Enter Sudoku puzzle (9x9 grid of numbers 0-9, 0 for empty):\n");
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (scanf("%d", &board[i][j]) != 1 || board[i][j] < 0 || board[i][j] > 9) {
                fprintf(stderr, "Invalid input.\n");
                return 1;
            }
        }
    }

    if (solve(0, 0)) {
        printf("Solved puzzle:\n");
        print_board();
    } else {
        printf("No solution found.\n");
    }
    return 0;
}
