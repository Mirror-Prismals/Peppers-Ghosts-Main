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

static void free_list(Node *head) {
    while (head) {
        Node *tmp = head->next;
        free(head);
        head = tmp;
    }
}

static int has_cycle(Node *head) {
    Node *slow = head;
    Node *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    int n;
    printf("Enter number of integers: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    int cycle_index;
    printf("Enter index to create cycle (-1 for none): ");
    if (scanf("%d", &cycle_index) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    Node *head = NULL;
    Node *tail = NULL;
    Node *cycle_node = NULL;

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; ++i) {
        int value;
        if (scanf("%d", &value) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free_list(head);
            return 1;
        }
        Node *node = create_node(value);
        if (!node) {
            perror("malloc");
            free_list(head);
            return 1;
        }
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        if (i == cycle_index) {
            cycle_node = node;
        }
    }

    if (cycle_node) {
        tail->next = cycle_node;
    }

    if (has_cycle(head)) {
        printf("Cycle detected.\n");
    } else {
        printf("No cycle detected.\n");
    }

    tail->next = NULL; // break cycle if any
    free_list(head);
    return 0;
}

