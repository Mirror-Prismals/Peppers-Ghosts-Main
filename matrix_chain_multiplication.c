#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void) {
    int n;
    printf("Enter number of matrices: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    int *p = malloc((n + 1) * sizeof(int));
    if (!p) {
        perror("malloc");
        return 1;
    }

    printf("Enter %d dimensions: ", n + 1);
    for (int i = 0; i <= n; ++i) {
        if (scanf("%d", &p[i]) != 1 || p[i] <= 0) {
            fprintf(stderr, "Invalid input.\n");
            free(p);
            return 1;
        }
    }

    int **m = malloc(n * sizeof(int*));
    if (!m) {
        perror("malloc");
        free(p);
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        m[i] = malloc(n * sizeof(int));
        if (!m[i]) {
            perror("malloc");
            for (int j = 0; j < i; ++j) free(m[j]);
            free(m);
            free(p);
            return 1;
        }
    }

    for (int i = 0; i < n; ++i) {
        m[i][i] = 0;
    }

    for (int l = 2; l <= n; ++l) {
        for (int i = 0; i <= n - l; ++i) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; ++k) {
                long long q = (long long)m[i][k] + m[k + 1][j] +
                                (long long)p[i] * p[k + 1] * p[j + 1];
                if (q < m[i][j]) {
                    m[i][j] = (int)q;
                }
            }
        }
    }

    printf("Minimum number of multiplications: %d\n", m[0][n - 1]);

    for (int i = 0; i < n; ++i) {
        free(m[i]);
    }
    free(m);
    free(p);
    return 0;
}

