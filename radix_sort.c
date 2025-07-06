#include <stdio.h>
#include <stdlib.h>

static int get_max(const int *arr, int n) {
    int max = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

static void counting_sort(int *arr, int n, int exp) {
    int *output = malloc(n * sizeof(int));
    int count[10] = {0};
    for (int i = 0; i < n; ++i) {
        int index = (arr[i] / exp) % 10;
        ++count[index];
    }
    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        int index = (arr[i] / exp) % 10;
        output[count[index] - 1] = arr[i];
        --count[index];
    }
    for (int i = 0; i < n; ++i) {
        arr[i] = output[i];
    }
    free(output);
}

static void radix_sort(int *arr, int n) {
    int max = get_max(arr, n);
    for (int exp = 1; max / exp > 0; exp *= 10) {
        counting_sort(arr, n, exp);
    }
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
    radix_sort(arr, n);
    printf("Sorted integers:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\n", arr[i]);
    }
    free(arr);
    return 0;
}
