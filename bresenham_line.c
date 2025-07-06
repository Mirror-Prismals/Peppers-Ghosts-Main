#include <stdio.h>
#include <stdlib.h>

static void plot_line(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy; // error value

    while (1) {
        printf("(%d, %d)\n", x0, y0);
        if (x0 == x1 && y0 == y1) {
            break;
        }
        int e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

int main(void) {
    int x0, y0, x1, y1;
    printf("Enter x0 y0 x1 y1: ");
    if (scanf("%d %d %d %d", &x0, &y0, &x1, &y1) != 4) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    plot_line(x0, y0, x1, y1);
    return 0;
}
