#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    unsigned char ch;
    unsigned freq;
    struct Node *left;
    struct Node *right;
} Node;

static Node *create_node(unsigned char ch, unsigned freq, Node *left, Node *right) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        perror("malloc");
        exit(1);
    }
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

static int cmp_nodes(const void *a, const void *b) {
    const Node *na = *(const Node **)a;
    const Node *nb = *(const Node **)b;
    return (int)na->freq - (int)nb->freq;
}

static void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

static void build_codes(Node *root, char codes[256][256], char *buffer, int depth) {
    if (!root->left && !root->right) {
        buffer[depth] = '\0';
        strcpy(codes[root->ch], buffer);
        printf("%c: %s\n", root->ch, codes[root->ch]);
        return;
    }
    if (root->left) {
        buffer[depth] = '0';
        build_codes(root->left, codes, buffer, depth + 1);
    }
    if (root->right) {
        buffer[depth] = '1';
        build_codes(root->right, codes, buffer, depth + 1);
    }
}

int main(void) {
    char input[1024];
    printf("Enter a string: ");
    if (!fgets(input, sizeof(input), stdin)) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    size_t len = strlen(input);
    if (len && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        --len;
    }
    if (len == 0) {
        fprintf(stderr, "Empty input.\n");
        return 1;
    }

    unsigned freq[256] = {0};
    for (size_t i = 0; i < len; ++i) {
        ++freq[(unsigned char)input[i]];
    }

    Node *nodes[256];
    int count = 0;
    for (int i = 0; i < 256; ++i) {
        if (freq[i]) {
            nodes[count++] = create_node((unsigned char)i, freq[i], NULL, NULL);
        }
    }

    if (count == 1) {
        nodes[count++] = create_node(0, 0, NULL, NULL); /* dummy node */
    }

    while (count > 1) {
        qsort(nodes, (size_t)count, sizeof(Node *), cmp_nodes);
        Node *left = nodes[0];
        Node *right = nodes[1];
        Node *parent = create_node(0, left->freq + right->freq, left, right);
        for (int i = 2; i < count; ++i) {
            nodes[i - 2] = nodes[i];
        }
        count -= 2;
        nodes[count++] = parent;
    }

    Node *root = nodes[0];

    printf("Huffman Codes:\n");
    char codes[256][256] = {{0}};
    char buffer[256];
    build_codes(root, codes, buffer, 0);

    printf("Encoded string: ");
    for (size_t i = 0; i < len; ++i) {
        fputs(codes[(unsigned char)input[i]], stdout);
    }
    putchar('\n');

    free_tree(root);
    return 0;
}

