#include <stdio.h>
#include <stdlib.h>

static void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static int partition(int *arr, int left, int right) {
    int pivot = arr[right];
    int i = left;
    for (int j = left; j < right; ++j) {
        if (arr[j] < pivot) {
            swap(&arr[i], &arr[j]);
            ++i;
        }
    }
    swap(&arr[i], &arr[right]);
    return i;
}

static int quickselect(int *arr, int left, int right, int k) {
    while (left <= right) {
        int pivot_index = partition(arr, left, right);
        if (pivot_index == k) {
            return arr[pivot_index];
        } else if (k < pivot_index) {
            right = pivot_index - 1;
        } else {
            left = pivot_index + 1;
        }
    }
    return arr[left];
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
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(arr);
            return 1;
        }
    }
    int k;
    printf("Enter k (1-%d): ", n);
    if (scanf("%d", &k) != 1 || k < 1 || k > n) {
        fprintf(stderr, "Invalid input.\n");
        free(arr);
        return 1;
    }
    int result = quickselect(arr, 0, n - 1, k - 1);
    printf("The %d-th smallest element is %d\n", k, result);
    free(arr);
    return 0;
}

