#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

static int height(Node *n) {
    return n ? n->height : 0;
}

static int max(int a, int b) {
    return (a > b) ? a : b;
}

static Node *new_node(int key) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

static Node *right_rotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

static Node *left_rotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

static int get_balance(Node *n) {
    return n ? height(n->left) - height(n->right) : 0;
}

static Node *insert(Node *node, int key) {
    if (node == NULL)
        return new_node(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;
    node->height = 1 + max(height(node->left), height(node->right));
    int balance = get_balance(node);
    if (balance > 1 && key < node->left->key)
        return right_rotate(node);
    if (balance < -1 && key > node->right->key)
        return left_rotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    return node;
}

static Node *min_value_node(Node *node) {
    Node *current = node;
    while (current->left)
        current = current->left;
    return current;
}

static Node *delete_node(Node *root, int key) {
    if (!root)
        return root;
    if (key < root->key)
        root->left = delete_node(root->left, key);
    else if (key > root->key)
        root->right = delete_node(root->right, key);
    else {
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
            root->key = temp->key;
            root->right = delete_node(root->right, temp->key);
        }
    }
    if (!root)
        return root;
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = get_balance(root);
    if (balance > 1 && get_balance(root->left) >= 0)
        return right_rotate(root);
    if (balance > 1 && get_balance(root->left) < 0) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    if (balance < -1 && get_balance(root->right) <= 0)
        return left_rotate(root);
    if (balance < -1 && get_balance(root->right) > 0) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    return root;
}

static void pre_order(Node *root) {
    if (root) {
        printf("%d ", root->key);
        pre_order(root->left);
        pre_order(root->right);
    }
}

int main(void) {
    Node *root = NULL;
    int keys[] = {10, 20, 30, 40, 50, 25};
    for (size_t i = 0; i < sizeof(keys)/sizeof(keys[0]); ++i)
        root = insert(root, keys[i]);
    printf("Preorder traversal after insertion:\n");
    pre_order(root);
    printf("\n");
    root = delete_node(root, 40);
    printf("Preorder traversal after deletion of 40:\n");
    pre_order(root);
    printf("\n");
    return 0;
}
