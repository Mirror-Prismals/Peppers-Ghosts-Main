#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int *arr, int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
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
    insertion_sort(arr, n);
    printf("Sorted integers:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\n", arr[i]);
    }
    free(arr);
    return 0;
}
