#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void) {
    char mode;
    printf("Encrypt or decrypt? (e/d): ");
    if (scanf(" %c", &mode) != 1 || (mode != 'e' && mode != 'd')) {
        fprintf(stderr, "Invalid mode.\n");
        return 1;
    }

    char key[256];
    printf("Enter key (letters only): ");
    if (scanf("%255s", key) != 1) {
        fprintf(stderr, "Invalid key.\n");
        return 1;
    }
    size_t key_len = strlen(key);
    for (size_t i = 0; i < key_len; ++i) {
        if (!isalpha((unsigned char)key[i])) {
            fprintf(stderr, "Key must contain only letters.\n");
            return 1;
        }
        key[i] = (char)toupper((unsigned char)key[i]);
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        ;
    }

    char text[1024];
    printf("Enter text: ");
    if (!fgets(text, sizeof(text), stdin)) {
        return 1;
    }
    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[--len] = '\0';
    }

    for (size_t i = 0, j = 0; i < len; ++i) {
        char ch = text[i];
        if (isalpha((unsigned char)ch)) {
            int shift = key[j % key_len] - 'A';
            char base = isupper((unsigned char)ch) ? 'A' : 'a';
            if (mode == 'd') {
                text[i] = (char)((((ch - base - shift) + 26) % 26) + base);
            } else {
                text[i] = (char)(((ch - base + shift) % 26) + base);
            }
            ++j;
        }
    }

    printf("Result: %s\n", text);
    return 0;
}

