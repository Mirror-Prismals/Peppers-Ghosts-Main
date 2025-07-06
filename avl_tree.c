#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

static int height(Node *node) {
    return node ? node->height : 0;
}

static int max(int a, int b) {
    return a > b ? a : b;
}

static Node *create_node(int value) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        return NULL;
    }
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

static Node *right_rotate(Node *y) {
    Node *x = y->left;
    Node *t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

static Node *left_rotate(Node *x) {
    Node *y = x->right;
    Node *t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

static int get_balance(Node *node) {
    return node ? height(node->left) - height(node->right) : 0;
}

static Node *insert(Node *node, int value) {
    if (!node) {
        return create_node(value);
    }
    if (value < node->value) {
        node->left = insert(node->left, value);
    } else if (value > node->value) {
        node->right = insert(node->right, value);
    } else {
        return node; /* no duplicates */
    }

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = get_balance(node);

    if (balance > 1 && value < node->left->value) {
        return right_rotate(node);
    }
    if (balance < -1 && value > node->right->value) {
        return left_rotate(node);
    }
    if (balance > 1 && value > node->left->value) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    if (balance < -1 && value < node->right->value) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

static Node *min_value_node(Node *node) {
    Node *current = node;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

static Node *delete_node(Node *root, int value) {
    if (!root) {
        return root;
    }
    if (value < root->value) {
        root->left = delete_node(root->left, value);
    } else if (value > root->value) {
        root->right = delete_node(root->right, value);
    } else {
        if (!root->left || !root->right) {
            Node *temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            Node *temp = min_value_node(root->right);
            root->value = temp->value;
            root->right = delete_node(root->right, temp->value);
        }
    }

    if (!root) {
        return root;
    }

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = get_balance(root);

    if (balance > 1 && get_balance(root->left) >= 0) {
        return right_rotate(root);
    }
    if (balance > 1 && get_balance(root->left) < 0) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    if (balance < -1 && get_balance(root->right) <= 0) {
        return left_rotate(root);
    }
    if (balance < -1 && get_balance(root->right) > 0) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

static Node *search(Node *root, int value) {
    if (!root || root->value == value) {
        return root;
    }
    if (value < root->value) {
        return search(root->left, value);
    }
    return search(root->right, value);
}

static void inorder(Node *root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
}

static void free_tree(Node *root) {
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
        Node *new_root = insert(root, value);
        if (!new_root) {
            perror("insert");
            free_tree(root);
            return 1;
        }
        root = new_root;
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
    root = delete_node(root, key);

    printf("In-order traversal after deletion: ");
    inorder(root);
    printf("\n");

    free_tree(root);
    return 0;
}
