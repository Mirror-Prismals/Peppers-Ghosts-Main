#include <stdio.h>
#include <stdlib.h>

/* Kadane's algorithm for maximum subarray sum */
static int max_subarray_sum(const int *arr, int n) {
    int max_so_far = arr[0];
    int curr_max = arr[0];
    for (int i = 1; i < n; ++i) {
        if (curr_max < 0) {
            curr_max = arr[i];
        } else {
            curr_max += arr[i];
        }
        if (curr_max > max_so_far) {
            max_so_far = curr_max;
        }
    }
    return max_so_far;
}

int main(void) {
    int n;
    printf("Enter number of integers: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    int *arr = malloc(n * sizeof(int));
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
    int result = max_subarray_sum(arr, n);
    printf("Maximum subarray sum: %d\n", result);
    free(arr);
    return 0;
}
