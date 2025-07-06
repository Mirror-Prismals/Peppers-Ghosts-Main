#include <stdio.h>
#include <stdlib.h>

static int ternary_search(const int *arr, int size, int key) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int third = (right - left) / 3;
        int mid1 = left + third;
        int mid2 = right - third;
        if (arr[mid1] == key) {
            return mid1;
        }
        if (arr[mid2] == key) {
            return mid2;
        }
        if (key < arr[mid1]) {
            right = mid1 - 1;
        } else if (key > arr[mid2]) {
            left = mid2 + 1;
        } else {
            left = mid1 + 1;
            right = mid2 - 1;
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
    int idx = ternary_search(arr, n, key);
    if (idx >= 0) {
        printf("Found %d at index %d\n", key, idx);
    } else {
        printf("%d not found\n", key);
    }
    free(arr);
    return 0;
}
