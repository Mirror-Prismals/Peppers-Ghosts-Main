#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int steps;
    printf("Enter number of steps: ");
    if (scanf("%d", &steps) != 1 || steps <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    srand((unsigned)time(NULL));
    int position = 0;
    printf("0,%d\n", position);
    for (int i = 1; i <= steps; ++i) {
        position += (rand() % 2) ? 1 : -1;
        printf("%d,%d\n", i, position);
    }
    return 0;
}
