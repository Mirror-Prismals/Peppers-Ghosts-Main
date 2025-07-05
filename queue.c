#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int head;
    int tail;
    int size;
    int capacity;
} Queue;

static Queue *create_queue(int capacity) {
    Queue *q = malloc(sizeof(Queue));
    if (!q) {
        return NULL;
    }
    q->data = malloc(capacity * sizeof(int));
    if (!q->data) {
        free(q);
        return NULL;
    }
    q->head = 0;
    q->tail = 0;
    q->size = 0;
    q->capacity = capacity;
    return q;
}

static int enqueue(Queue *q, int value) {
    if (q->size >= q->capacity) {
        return -1; // full
    }
    q->data[q->tail] = value;
    q->tail = (q->tail + 1) % q->capacity;
    q->size++;
    return 0;
}

static int dequeue(Queue *q, int *value) {
    if (q->size <= 0) {
        return -1; // empty
    }
    *value = q->data[q->head];
    q->head = (q->head + 1) % q->capacity;
    q->size--;
    return 0;
}

static void free_queue(Queue *q) {
    if (q) {
        free(q->data);
        free(q);
    }
}

int main(void) {
    int n;
    printf("Enter queue capacity: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid capacity.\n");
        return 1;
    }
    Queue *q = create_queue(n);
    if (!q) {
        perror("create_queue");
        return 1;
    }
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; ++i) {
        int value;
        if (scanf("%d", &value) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free_queue(q);
            return 1;
        }
        if (enqueue(q, value) != 0) {
            fprintf(stderr, "Queue overflow.\n");
            free_queue(q);
            return 1;
        }
    }
    printf("Dequeuing integers:\n");
    int value;
    while (dequeue(q, &value) == 0) {
        printf("%d\n", value);
    }
    free_queue(q);
    return 0;
}
