#include <stdio.h>
#include <stdlib.h>

static void plot_circle(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;
    while (y >= x) {
        printf("(%d, %d)\n", xc + x, yc + y);
        printf("(%d, %d)\n", xc - x, yc + y);
        printf("(%d, %d)\n", xc + x, yc - y);
        printf("(%d, %d)\n", xc - x, yc - y);
        printf("(%d, %d)\n", xc + y, yc + x);
        printf("(%d, %d)\n", xc - y, yc + x);
        printf("(%d, %d)\n", xc + y, yc - x);
        printf("(%d, %d)\n", xc - y, yc - x);
        ++x;
        if (d > 0) {
            --y;
            d += 4 * (x - y) + 10;
        } else {
            d += 4 * x + 6;
        }
    }
}

int main(void) {
    int xc, yc, r;
    printf("Enter center x y and radius: ");
    if (scanf("%d %d %d", &xc, &yc, &r) != 3 || r <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    plot_circle(xc, yc, r);
    return 0;
}
