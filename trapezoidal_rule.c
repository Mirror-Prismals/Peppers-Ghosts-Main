#include <stdio.h>
#include <math.h>

/* Function to integrate: f(x) = sin(x) */
static double f(double x) {
    return sin(x);
}

/* Trapezoidal rule for numerical integration */
static double trapezoidal(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; ++i) {
        sum += f(a + i * h);
    }
    return h * sum;
}

int main(void) {
    double a, b;
    int n;
    printf("Integrate sin(x) from a to b using the trapezoidal rule.\n");
    printf("Enter a: ");
    if (scanf("%lf", &a) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    printf("Enter b (b > a): ");
    if (scanf("%lf", &b) != 1 || b <= a) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    printf("Enter the number of intervals: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    double result = trapezoidal(a, b, n);
    printf("Approximate integral = %.10f\n", result);
    return 0;
}
