#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node *create_node(int value) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        return NULL;
    }
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *insert(Node *root, int value) {
    if (!root) {
        return create_node(value);
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else if (value > root->value) {
        root->right = insert(root->right, value);
    }
    return root;
}

Node *search(Node *root, int value) {
    if (!root || root->value == value) {
        return root;
    }
    if (value < root->value) {
        return search(root->left, value);
    }
    return search(root->right, value);
}

Node *min_value_node(Node *node) {
    Node *current = node;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

Node *delete(Node *root, int value) {
    if (!root) {
        return root;
    }
    if (value < root->value) {
        root->left = delete(root->left, value);
    } else if (value > root->value) {
        root->right = delete(root->right, value);
    } else {
        if (!root->left) {
            Node *temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        Node *temp = min_value_node(root->right);
        root->value = temp->value;
        root->right = delete(root->right, temp->value);
    }
    return root;
}

void inorder(Node *root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
}

void free_tree(Node *root) {
    if (root) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main(void) {
    int n;
    printf("Enter number of integers: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    Node *root = NULL;
    for (int i = 0; i < n; ++i) {
        int value;
        if (scanf("%d", &value) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free_tree(root);
            return 1;
        }
        root = insert(root, value);
    }

    printf("In-order traversal: ");
    inorder(root);
    printf("\n");

    int key;
    printf("Enter value to search: ");
    if (scanf("%d", &key) != 1) {
        fprintf(stderr, "Invalid input.\n");
        free_tree(root);
        return 1;
    }
    Node *found = search(root, key);
    if (found) {
        printf("%d found in the tree.\n", key);
    } else {
        printf("%d not found in the tree.\n", key);
    }

    printf("Enter value to delete: ");
    if (scanf("%d", &key) != 1) {
        fprintf(stderr, "Invalid input.\n");
        free_tree(root);
        return 1;
    }
    root = delete(root, key);

    printf("In-order traversal after deletion: ");
    inorder(root);
    printf("\n");

    free_tree(root);
    return 0;
}

