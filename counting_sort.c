#include <stdio.h>
#include <stdlib.h>

/* Counting sort for non-negative integers */
static int counting_sort(int *arr, int n) {
    if (n <= 0) return 0;
    int max = arr[0];
    for (int i = 0; i < n; ++i) {
        if (arr[i] < 0) {
            fprintf(stderr, "Negative numbers not supported.\n");
            return -1;
        }
        if (arr[i] > max) max = arr[i];
    }
    int *count = calloc(max + 1, sizeof(int));
    if (!count) {
        perror("calloc");
        return -1;
    }
    for (int i = 0; i < n; ++i) {
        count[arr[i]]++;
    }
    int idx = 0;
    for (int i = 0; i <= max; ++i) {
        for (int j = 0; j < count[i]; ++j) {
            arr[idx++] = i;
        }
    }
    free(count);
    return 0;
}

int main(void) {
    int n;
    printf("Enter number of non-negative integers: ");
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
        if (scanf("%d", &arr[i]) != 1 || arr[i] < 0) {
            fprintf(stderr, "Invalid input.\n");
            free(arr);
            return 1;
        }
    }
    if (counting_sort(arr, n) != 0) {
        free(arr);
        return 1;
    }
    printf("Sorted integers:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\n", arr[i]);
    }
    free(arr);
    return 0;
}
