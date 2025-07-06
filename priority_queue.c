#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} PriorityQueue;

static PriorityQueue *create_queue(int capacity) {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    if (!pq) {
        return NULL;
    }
    pq->data = malloc(capacity * sizeof(int));
    if (!pq->data) {
        free(pq);
        return NULL;
    }
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void bubble_up(PriorityQueue *pq, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (pq->data[parent] <= pq->data[index]) {
            break;
        }
        swap(&pq->data[parent], &pq->data[index]);
        index = parent;
    }
}

static int insert(PriorityQueue *pq, int value) {
    if (pq->size >= pq->capacity) {
        return -1; // full
    }
    pq->data[pq->size] = value;
    bubble_up(pq, pq->size);
    pq->size++;
    return 0;
}

static void bubble_down(PriorityQueue *pq, int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;
        if (left < pq->size && pq->data[left] < pq->data[smallest]) {
            smallest = left;
        }
        if (right < pq->size && pq->data[right] < pq->data[smallest]) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }
        swap(&pq->data[smallest], &pq->data[index]);
        index = smallest;
    }
}

static int extract_min(PriorityQueue *pq, int *value) {
    if (pq->size <= 0) {
        return -1; // empty
    }
    *value = pq->data[0];
    pq->size--;
    pq->data[0] = pq->data[pq->size];
    bubble_down(pq, 0);
    return 0;
}

static void free_queue(PriorityQueue *pq) {
    if (pq) {
        free(pq->data);
        free(pq);
    }
}

int main(void) {
    int n;
    printf("Enter number of integers: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    PriorityQueue *pq = create_queue(n);
    if (!pq) {
        perror("create_queue");
        return 1;
    }
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; ++i) {
        int value;
        if (scanf("%d", &value) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free_queue(pq);
            return 1;
        }
        if (insert(pq, value) != 0) {
            fprintf(stderr, "Queue is full.\n");
            free_queue(pq);
            return 1;
        }
    }

    printf("Integers in ascending order:\n");
    int value;
    while (extract_min(pq, &value) == 0) {
        printf("%d\n", value);
    }
    free_queue(pq);
    return 0;
}
