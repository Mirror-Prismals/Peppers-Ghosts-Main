#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *prev;
    struct Node *next;
} Node;

static Node *create_node(int value) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        return NULL;
    }
    node->value = value;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

static void push_back(Node **head, Node **tail, int value) {
    Node *node = create_node(value);
    if (!node) {
        perror("malloc");
        exit(1);
    }
    node->prev = *tail;
    if (*tail) {
        (*tail)->next = node;
    } else {
        *head = node;
    }
    *tail = node;
}

static Node *search(Node *head, int value) {
    for (Node *cur = head; cur; cur = cur->next) {
        if (cur->value == value) {
            return cur;
        }
    }
    return NULL;
}

static int delete_value(Node **head, Node **tail, int value) {
    Node *node = search(*head, value);
    if (!node) {
        return 0;
    }
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        *head = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    } else {
        *tail = node->prev;
    }
    free(node);
    return 1;
}

static void print_forward(const Node *head) {
    for (const Node *cur = head; cur; cur = cur->next) {
        printf("%d ", cur->value);
    }
    putchar('\n');
}

static void print_backward(const Node *tail) {
    for (const Node *cur = tail; cur; cur = cur->prev) {
        printf("%d ", cur->value);
    }
    putchar('\n');
}

static void free_list(Node *head) {
    while (head) {
        Node *tmp = head->next;
        free(head);
        head = tmp;
    }
}

int main(void) {
    int n;
    printf("Enter number of integers: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    Node *head = NULL;
    Node *tail = NULL;
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; ++i) {
        int value;
        if (scanf("%d", &value) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free_list(head);
            return 1;
        }
        push_back(&head, &tail, value);
    }

    printf("List forward: ");
    print_forward(head);
    printf("List backward: ");
    print_backward(tail);

    int key;
    printf("Enter value to delete: ");
    if (scanf("%d", &key) != 1) {
        fprintf(stderr, "Invalid input.\n");
        free_list(head);
        return 1;
    }
    if (delete_value(&head, &tail, key)) {
        printf("%d deleted.\n", key);
    } else {
        printf("%d not found.\n", key);
    }

    printf("List after deletion: ");
    print_forward(head);

    free_list(head);
    return 0;
}

