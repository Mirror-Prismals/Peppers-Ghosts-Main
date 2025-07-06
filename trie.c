#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int is_end_of_word;
} TrieNode;

static TrieNode *create_node(void) {
    TrieNode *node = malloc(sizeof(TrieNode));
    if (!node) {
        return NULL;
    }
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        node->children[i] = NULL;
    }
    node->is_end_of_word = 0;
    return node;
}

static void insert(TrieNode *root, const char *word) {
    for (const char *p = word; *p; ++p) {
        if (*p < 'a' || *p > 'z') {
            continue; // skip non-lowercase characters
        }
        int index = *p - 'a';
        if (!root->children[index]) {
            root->children[index] = create_node();
            if (!root->children[index]) {
                perror("malloc");
                exit(1);
            }
        }
        root = root->children[index];
    }
    root->is_end_of_word = 1;
}

static int search(const TrieNode *root, const char *word) {
    for (const char *p = word; *p; ++p) {
        if (*p < 'a' || *p > 'z') {
            continue;
        }
        int index = *p - 'a';
        if (!root->children[index]) {
            return 0;
        }
        root = root->children[index];
    }
    return root->is_end_of_word;
}

static void free_trie(TrieNode *root) {
    if (!root) return;
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
        perror("malloc");
        return 1;
    }

    printf("Enter %d lowercase words:\n", n);
    for (int i = 0; i < n; ++i) {
        char word[101];
        if (scanf("%100s", word) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free_trie(root);
            return 1;
        }
        insert(root, word);
    }

    char query[101];
    printf("Enter word to search: ");
    if (scanf("%100s", query) != 1) {
        fprintf(stderr, "Invalid input.\n");
        free_trie(root);
        return 1;
    }

    if (search(root, query)) {
        printf("%s found.\n", query);
    } else {
        printf("%s not found.\n", query);
    }

    free_trie(root);
    return 0;
}
