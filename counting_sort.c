#include <stdio.h>
#include <stdlib.h>

static void counting_sort(int *arr, int n, int max_val) {
    int *count = calloc((size_t)max_val + 1, sizeof(int));
    if (!count) {
        perror("calloc");
        exit(1);
    }
    for (int i = 0; i < n; ++i) {
        ++count[arr[i]];
    }
    int idx = 0;
    for (int i = 0; i <= max_val; ++i) {
        while (count[i]-- > 0) {
            arr[idx++] = i;
        }
    }
    free(count);
}

int main(void) {
    int n;
    printf("Enter number of integers: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    int max_val;
    printf("Enter maximum value: ");
    if (scanf("%d", &max_val) != 1 || max_val < 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    int *arr = malloc((size_t)n * sizeof(int));
    if (!arr) {
        perror("malloc");
        return 1;
    }
    printf("Enter %d integers between 0 and %d:\n", n, max_val);
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1 || arr[i] < 0 || arr[i] > max_val) {
            fprintf(stderr, "Invalid input.\n");
            free(arr);
            return 1;
        }
    }
    counting_sort(arr, n, max_val);
    printf("Sorted integers:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\n", arr[i]);
    }
    free(arr);
    return 0;
}
