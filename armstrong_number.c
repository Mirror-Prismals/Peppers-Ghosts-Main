#include <stdio.h>
#include <math.h>

static int is_armstrong(int n) {
    if (n < 0) return 0;
    int digits = 0;
    int temp = n;
    if (temp == 0) {
        digits = 1;
    } else {
        while (temp != 0) {
            ++digits;
            temp /= 10;
        }
    }
    temp = n;
    int sum = 0;
    while (temp != 0) {
        int d = temp % 10;
        sum += (int)round(pow(d, digits));
        temp /= 10;
    }
    return sum == n;
}

int main(void) {
    int n;
    printf("Enter a non-negative integer: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    if (is_armstrong(n)) {
        printf("%d is an Armstrong number.\n", n);
    } else {
        printf("%d is not an Armstrong number.\n", n);
    }
    return 0;
}
