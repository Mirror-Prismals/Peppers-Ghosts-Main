#include <stdio.h>
#include <stdlib.h>

static int interpolation_search(const int *arr, int size, int key) {
    int low = 0;
    int high = size - 1;
    while (low <= high && key >= arr[low] && key <= arr[high]) {
        if (arr[high] == arr[low]) {
            if (arr[low] == key) {
                return low;
            }
            break;
        }
        int pos = low + (int)((double)(high - low) * (key - arr[low]) / (arr[high] - arr[low]));
        if (pos < low || pos > high) {
            break;
        }
        if (arr[pos] == key) {
            return pos;
        } else if (arr[pos] < key) {
            low = pos + 1;
        } else {
            high = pos - 1;
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
    int key;
    printf("Enter value to search for: ");
    if (scanf("%d", &key) != 1) {
        fprintf(stderr, "Invalid input.\n");
        free(arr);
        return 1;
    }
    int idx = interpolation_search(arr, n, key);
    if (idx >= 0) {
        printf("Found %d at index %d\n", key, idx);
    } else {
        printf("%d not found\n", key);
    }
    free(arr);
    return 0;
}
