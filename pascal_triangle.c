#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int rows;
    printf("Enter number of rows: ");
    if (scanf("%d", &rows) != 1 || rows <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    unsigned long long *row = calloc(rows, sizeof(unsigned long long));
    if (!row) {
        perror("calloc");
        return 1;
    }
    row[0] = 1ULL;
    for (int i = 0; i < rows; ++i) {
        for (int j = i; j > 0; --j) {
            row[j] += row[j - 1];
        }
        for (int j = 0; j <= i; ++j) {
            printf("%llu%s", row[j], j == i ? "" : " ");
        }
        putchar('\n');
    }
    free(row);
    return 0;
}
