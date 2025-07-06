#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid array size.\n");
        return 1;
    }

    int *arr = malloc((size_t)n * sizeof(int));
    if (!arr) {
        perror("malloc");
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(arr);
            return 1;
        }
    }

    int candidate = arr[0];
    int count = 1;
    for (int i = 1; i < n; ++i) {
        if (arr[i] == candidate) {
            ++count;
        } else if (--count == 0) {
            candidate = arr[i];
            count = 1;
        }
    }

    count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] == candidate) {
            ++count;
        }
    }

    if (count > n / 2) {
        printf("Majority element: %d\n", candidate);
    } else {
        printf("No majority element\n");
    }

    free(arr);
    return 0;
}
