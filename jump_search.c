#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int jump_search(const int *arr, int size, int key) {
    if (size <= 0) {
        return -1;
    }
    int step = (int)sqrt(size);
    if (step < 1) step = 1;
    int prev = 0;
    while (prev < size && arr[(step < size ? step : size) - 1] < key) {
        prev = step;
        step += (int)sqrt(size);
        if (prev >= size) {
            return -1;
        }
    }
    for (int i = prev; i < step && i < size; ++i) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

int main(void) {
    int n;
    printf("Enter number of sorted integers: ");
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
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(arr);
            return 1;
        }
    }
    int key;
    printf("Enter value to search for: ");
    if (scanf("%d", &key) != 1) {
        fprintf(stderr, "Invalid input.\n");
        free(arr);
        return 1;
    }
    int idx = jump_search(arr, n, key);
    if (idx >= 0) {
        printf("Found %d at index %d\n", key, idx);
    } else {
        printf("%d not found\n", key);
    }
    free(arr);
    return 0;
}

