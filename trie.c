#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int is_end;
} TrieNode;

static TrieNode *create_node(void) {
    TrieNode *node = calloc(1, sizeof(TrieNode));
    return node;
}

static void insert(TrieNode *root, const char *word) {
    for (const char *p = word; *p; ++p) {
        char c = tolower((unsigned char)*p);
        if (c < 'a' || c > 'z') {
            continue;
        }
        int idx = c - 'a';
        if (!root->children[idx]) {
            root->children[idx] = create_node();
        }
        root = root->children[idx];
    }
    root->is_end = 1;
}

static int search(const TrieNode *root, const char *word) {
    for (const char *p = word; *p; ++p) {
        char c = tolower((unsigned char)*p);
        if (c < 'a' || c > 'z') {
            return 0;
        }
        int idx = c - 'a';
        root = root->children[idx];
        if (!root) {
            return 0;
        }
    }
    return root->is_end;
}

static void free_trie(TrieNode *root) {
    if (!root) {
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        free_trie(root->children[i]);
    }
    free(root);
}

int main(void) {
    int n;
    printf("Enter number of words: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    TrieNode *root = create_node();
    if (!root) {
        perror("calloc");
        return 1;
    }
    char buffer[256];
    printf("Enter %d words:\n", n);
    for (int i = 0; i < n; ++i) {
        if (scanf("%255s", buffer) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free_trie(root);
            return 1;
        }
        insert(root, buffer);
    }
    printf("Enter word to search: ");
    if (scanf("%255s", buffer) != 1) {
        fprintf(stderr, "Invalid input.\n");
        free_trie(root);
        return 1;
    }
    if (search(root, buffer)) {
        printf("\"%s\" is present.\n", buffer);
    } else {
        printf("\"%s\" is not present.\n", buffer);
    }
    free_trie(root);
    return 0;
}

