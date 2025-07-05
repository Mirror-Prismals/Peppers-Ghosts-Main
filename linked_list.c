#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static Node *create_node(int value) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        return NULL;
    }
    node->value = value;
    node->next = NULL;
    return node;
}

static void push_front(Node **head, int value) {
    Node *node = create_node(value);
    if (!node) {
        perror("malloc");
        exit(1);
    }
    node->next = *head;
    *head = node;
}

static Node *search(Node *head, int value) {
    for (Node *cur = head; cur; cur = cur->next) {
        if (cur->value == value) {
            return cur;
        }
    }
    return NULL;
}

static int delete_value(Node **head, int value) {
    Node **cur = head;
    while (*cur) {
        if ((*cur)->value == value) {
            Node *tmp = *cur;
            *cur = tmp->next;
            free(tmp);
            return 1;
        }
        cur = &(*cur)->next;
    }
    return 0;
}

static void print_list(const Node *head) {
    for (const Node *cur = head; cur; cur = cur->next) {
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
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; ++i) {
        int value;
        if (scanf("%d", &value) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free_list(head);
            return 1;
        }
        push_front(&head, value);
    }

    printf("List contents: ");
    print_list(head);

    int key;
    printf("Enter value to search: ");
    if (scanf("%d", &key) != 1) {
        fprintf(stderr, "Invalid input.\n");
        free_list(head);
        return 1;
    }
    if (search(head, key)) {
        printf("%d found in the list.\n", key);
    } else {
        printf("%d not found in the list.\n", key);
    }

    printf("Enter value to delete: ");
    if (scanf("%d", &key) != 1) {
        fprintf(stderr, "Invalid input.\n");
        free_list(head);
        return 1;
    }
    if (delete_value(&head, key)) {
        printf("%d deleted.\n", key);
    } else {
        printf("%d not found.\n", key);
    }

    printf("List after deletion: ");
    print_list(head);

    free_list(head);
    return 0;
}

