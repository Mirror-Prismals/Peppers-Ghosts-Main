#include <stdio.h>

static int extended_gcd(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int x1, y1;
    int g = extended_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - y1 * (a / b);
    return g;
}

int main(void) {
    int a, b;
    printf("Enter two integers: ");
    if (scanf("%d %d", &a, &b) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    int x, y;
    int g = extended_gcd(a, b, &x, &y);
    printf("gcd(%d, %d) = %d\n", a, b, g);
    printf("Coefficients x and y: %d %d\n", x, y);
    return 0;
}
