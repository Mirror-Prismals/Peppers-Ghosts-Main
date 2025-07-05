#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int top;
    int capacity;
} Stack;

Stack *create_stack(int capacity) {
    Stack *s = malloc(sizeof(Stack));
    if (!s) {
        return NULL;
    }
    s->data = malloc(capacity * sizeof(int));
    if (!s->data) {
        free(s);
        return NULL;
    }
    s->top = -1;
    s->capacity = capacity;
    return s;
}

int push(Stack *s, int value) {
    if (s->top >= s->capacity - 1) {
        return -1; // full
    }
    s->data[++s->top] = value;
    return 0;
}

int pop(Stack *s, int *value) {
    if (s->top < 0) {
        return -1; // empty
    }
    *value = s->data[s->top--];
    return 0;
}

void free_stack(Stack *s) {
    if (s) {
        free(s->data);
        free(s);
    }
}

int main(void) {
    int n;
    printf("Enter stack capacity: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid capacity.\n");
        return 1;
    }
    Stack *s = create_stack(n);
    if (!s) {
        perror("create_stack");
        return 1;
    }
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; ++i) {
        int value;
        if (scanf("%d", &value) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free_stack(s);
            return 1;
        }
        if (push(s, value) != 0) {
            fprintf(stderr, "Stack overflow.\n");
            free_stack(s);
            return 1;
        }
    }
    printf("Popping integers:\n");
    int value;
    while (pop(s, &value) == 0) {
        printf("%d\n", value);
    }
    free_stack(s);
    return 0;
}
