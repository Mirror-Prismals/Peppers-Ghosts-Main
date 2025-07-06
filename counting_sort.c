#include <stdio.h>
#include <stdlib.h>

static void counting_sort(int *arr, int n) {
    int max = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    int *count = calloc((size_t)(max + 1), sizeof(int));
    if (!count) {
        perror("calloc");
        exit(1);
    }
    for (int i = 0; i < n; ++i) {
        ++count[arr[i]];
    }
    int index = 0;
    for (int i = 0; i <= max; ++i) {
        while (count[i]-- > 0) {
            arr[index++] = i;
        }
    }
    free(count);
}

int main(void) {
    int n;
    printf("Enter number of non-negative integers: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    int *arr = malloc((size_t)n * sizeof(int));
    if (!arr) {
        perror("malloc");
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1 || arr[i] < 0) {
            fprintf(stderr, "Invalid input.\n");
            free(arr);
            return 1;
        }
    }
    counting_sort(arr, n);
    printf("Sorted integers:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\n", arr[i]);
    }
    free(arr);
    return 0;
}

