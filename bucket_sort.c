#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float *data;
    int size;
    int capacity;
} Bucket;

static void bucket_init(Bucket *b) {
    b->size = 0;
    b->capacity = 4;
    b->data = malloc(b->capacity * sizeof(float));
    if (!b->data) {
        perror("malloc");
        exit(1);
    }
}

static void bucket_push(Bucket *b, float value) {
    if (b->size == b->capacity) {
        b->capacity *= 2;
        float *tmp = realloc(b->data, b->capacity * sizeof(float));
        if (!tmp) {
            perror("realloc");
            exit(1);
        }
        b->data = tmp;
    }
    b->data[b->size++] = value;
}

static void insertion_sort(float *arr, int n) {
    for (int i = 1; i < n; ++i) {
        float key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

static void bucket_sort(float *arr, int n) {
    Bucket *buckets = malloc(n * sizeof(Bucket));
    if (!buckets) {
        perror("malloc");
        exit(1);
    }
    for (int i = 0; i < n; ++i) {
        bucket_init(&buckets[i]);
    }
    for (int i = 0; i < n; ++i) {
        int idx = (int)(arr[i] * n);
        if (idx >= n) idx = n - 1;
        bucket_push(&buckets[idx], arr[i]);
    }
    int pos = 0;
    for (int i = 0; i < n; ++i) {
        if (buckets[i].size > 0) {
            insertion_sort(buckets[i].data, buckets[i].size);
            for (int j = 0; j < buckets[i].size; ++j) {
                arr[pos++] = buckets[i].data[j];
            }
        }
        free(buckets[i].data);
    }
    free(buckets);
}

int main(void) {
    int n;
    printf("Enter number of floating point numbers: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    float *arr = malloc(n * sizeof(float));
    if (!arr) {
        perror("malloc");
        return 1;
    }
    printf("Enter %d numbers in [0,1):\n", n);
    for (int i = 0; i < n; ++i) {
        if (scanf("%f", &arr[i]) != 1 || arr[i] < 0.0f || arr[i] >= 1.0f) {
            fprintf(stderr, "Invalid input.\n");
            free(arr);
            return 1;
        }
    }
    bucket_sort(arr, n);
    printf("Sorted numbers:\n");
    for (int i = 0; i < n; ++i) {
        printf("%f\n", arr[i]);
    }
    free(arr);
    return 0;
}
