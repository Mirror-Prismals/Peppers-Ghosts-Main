#include <stdio.h>
#include <math.h>

/* Function to integrate: f(x) = sin(x) */
static double f(double x) {
    return sin(x);
}

/* Simpson's rule for numerical integration */
static double simpson(double a, double b, int n) {
    double h = (b - a) / n;
    double sum1 = 0.0; /* terms with coefficient 4 */
    double sum2 = 0.0; /* terms with coefficient 2 */
    for (int i = 1; i < n; i += 2) {
        sum1 += f(a + i * h);
    }
    for (int i = 2; i < n; i += 2) {
        sum2 += f(a + i * h);
    }
    return (h / 3.0) * (f(a) + f(b) + 4.0 * sum1 + 2.0 * sum2);
}

int main(void) {
    double a, b;
    int n;
    printf("Integrate sin(x) from a to b using Simpson's rule.\n");
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
    printf("Enter an even number of intervals: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n % 2 != 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    double result = simpson(a, b, n);
    printf("Approximate integral = %.10f\n", result);
    return 0;
}
