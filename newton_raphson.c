#include <stdio.h>
#include <math.h>

/* Function for which we seek a root: f(x) = x^3 - x - 2 */
static double f(double x) {
    return x * x * x - x - 2.0;
}

/* Derivative of f(x): f'(x) = 3x^2 - 1 */
static double f_prime(double x) {
    return 3.0 * x * x - 1.0;
}

/* Newton-Raphson method to approximate a root of f(x) */
static double newton_raphson(double guess, double tol, int max_iter) {
    double x = guess;
    for (int i = 0; i < max_iter; ++i) {
        double fx = f(x);
        double dfx = f_prime(x);
        if (dfx == 0.0) {
            break; /* avoid division by zero */
        }
        double next = x - fx / dfx;
        if (fabs(next - x) < tol) {
            return next;
        }
        x = next;
    }
    return x;
}

int main(void) {
    double guess;
    printf("Enter initial guess: ");
    if (scanf("%lf", &guess) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    double root = newton_raphson(guess, 1e-7, 1000);
    printf("Approximate root: %.10f\n", root);
    printf("f(root) = %.10f\n", f(root));
    return 0;
}

