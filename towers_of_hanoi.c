#include <stdio.h>

void move_disks(int n, char from, char to, char aux, int *step) {
    if (n == 0) {
        return;
    }
    move_disks(n - 1, from, aux, to, step);
    printf("%d: Move disk %d from %c to %c\n", (*step)++, n, from, to);
    move_disks(n - 1, aux, to, from, step);
}

int main(void) {
    int n;
    printf("Enter number of disks: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    int step = 1;
    move_disks(n, 'A', 'C', 'B', &step);
    printf("Total moves: %d\n", step - 1);
    return 0;
}
