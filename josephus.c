#include <stdio.h>
#include <stdlib.h>

static int josephus(int n, int k) {
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        res = (res + k) % i;
    }
    return res + 1; // convert to 1-based index
}

int main(void) {
    int n, k;
    printf("Enter number of people and step: ");
    if (scanf("%d %d", &n, &k) != 2 || n <= 0 || k <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    int safe_pos = josephus(n, k);
    printf("Safe position: %d\n", safe_pos);
    return 0;
}
