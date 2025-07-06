#include <stdio.h>
#include <stdlib.h>

static void flip(int *arr, int i) {
    int start = 0;
    while (start < i) {
        int temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
        ++start;
        --i;
    }
}

static int find_max_index(const int *arr, int n) {
    int max_idx = 0;
    for (int i = 1; i <= n; ++i) {
        if (arr[i] > arr[max_idx]) {
            max_idx = i;
        }
    }
    return max_idx;
}

static void pancake_sort(int *arr, int n) {
    for (int curr_size = n - 1; curr_size > 0; --curr_size) {
        int max_idx = find_max_index(arr, curr_size);
        if (max_idx != curr_size) {
            flip(arr, max_idx);
            flip(arr, curr_size);
        }
    }
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
    pancake_sort(arr, n);
    printf("Sorted integers:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\n", arr[i]);
    }
    free(arr);
    return 0;
}
