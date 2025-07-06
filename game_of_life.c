#include <stdio.h>

#define ROWS 20
#define COLS 20
#define GENERATIONS 20

static void print_grid(int grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            putchar(grid[i][j] ? '#' : '.');
        }
        putchar('\n');
    }
}

static int count_neighbors(int grid[ROWS][COLS], int x, int y) {
    int count = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0)
                continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS)
                count += grid[nx][ny];
        }
    }
    return count;
}

static void step(int grid[ROWS][COLS]) {
    int next[ROWS][COLS] = {0};
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int n = count_neighbors(grid, i, j);
            if (grid[i][j]) {
                next[i][j] = (n == 2 || n == 3);
            } else {
                next[i][j] = (n == 3);
            }
        }
    }
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            grid[i][j] = next[i][j];
        }
    }
}

int main(void) {
    int grid[ROWS][COLS] = {0};

    /* glider pattern */
    grid[1][2] = 1;
    grid[2][3] = 1;
    grid[3][1] = 1;
    grid[3][2] = 1;
    grid[3][3] = 1;

    for (int gen = 0; gen < GENERATIONS; ++gen) {
        printf("Generation %d:\n", gen);
        print_grid(grid);
        step(grid);
        putchar('\n');
    }
    return 0;
}

