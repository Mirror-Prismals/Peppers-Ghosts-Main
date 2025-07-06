#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Simple Huffman coding implementation for ASCII characters */

typedef struct Node {
    unsigned char ch;
    unsigned freq;
    struct Node *left;
    struct Node *right;
} Node;

static Node *create_node(unsigned char ch, unsigned freq, Node *left, Node *right) {
    Node *n = malloc(sizeof(Node));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->ch = ch;
    n->freq = freq;
    n->left = left;
    n->right = right;
    return n;
}

static void free_tree(Node *root) {
    if (root) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

static void build_codes(Node *root, char *prefix, int depth, char codes[256][256]) {
    if (!root) return;
    if (!root->left && !root->right) {
        prefix[depth] = '\0';
        strcpy(codes[root->ch], prefix);
        return;
    }
    prefix[depth] = '0';
    build_codes(root->left, prefix, depth + 1, codes);
    prefix[depth] = '1';
    build_codes(root->right, prefix, depth + 1, codes);
}

int main(void) {
    char input[1024];
    printf("Enter a string: ");
    if (!fgets(input, sizeof(input), stdin)) {
        return 1;
    }
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[--len] = '\0';
    }
    if (len == 0) {
        printf("Empty input.\n");
        return 0;
    }

    unsigned freq[256] = {0};
    for (size_t i = 0; i < len; ++i) {
        ++freq[(unsigned char)input[i]];
    }

    Node *list[512];
    size_t n = 0;
    for (int i = 0; i < 256; ++i) {
        if (freq[i]) {
            list[n++] = create_node((unsigned char)i, freq[i], NULL, NULL);
        }
    }

    while (n > 1) {
        size_t min1 = 0, min2 = 1;
        if (list[min2]->freq < list[min1]->freq) {
            size_t tmp = min1; min1 = min2; min2 = tmp;
        }
        for (size_t i = 2; i < n; ++i) {
            if (list[i]->freq < list[min1]->freq) {
                min2 = min1;
                min1 = i;
            } else if (list[i]->freq < list[min2]->freq) {
                min2 = i;
            }
        }
        if (min1 > min2) {
            size_t tmp = min1; min1 = min2; min2 = tmp;
        }
        Node *left = list[min1];
        Node *right = list[min2];
        Node *parent = create_node(0, left->freq + right->freq, left, right);
        for (size_t i = min2 + 1; i < n; ++i) list[i - 1] = list[i];
        --n;
        for (size_t i = min1 + 1; i < n; ++i) list[i - 1] = list[i];
        --n;
        list[n++] = parent;
    }
    Node *root = list[0];

    char codes[256][256] = {{0}};
    char prefix[256];
    build_codes(root, prefix, 0, codes);

    printf("Character codes:\n");
    for (int i = 0; i < 256; ++i) {
        if (freq[i]) {
            if (isprint(i)) {
                printf("'%c' (%d): %s\n", i, i, codes[i]);
            } else {
                printf("0x%02x (%d): %s\n", i, i, codes[i]);
            }
        }
    }

    printf("Encoded string:\n");
    for (size_t i = 0; i < len; ++i) {
        printf("%s", codes[(unsigned char)input[i]]);
    }
    printf("\n");

    free_tree(root);
    return 0;
}

