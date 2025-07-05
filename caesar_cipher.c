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

    int shift;
    printf("Enter shift (1-25): ");
    if (scanf("%d", &shift) != 1 || shift < 1 || shift > 25) {
        fprintf(stderr, "Invalid shift.\n");
        return 1;
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

    if (mode == 'd') {
        shift = 26 - shift;
    }

    for (size_t i = 0; i < len; ++i) {
        char ch = text[i];
        if (isalpha((unsigned char)ch)) {
            char base = isupper((unsigned char)ch) ? 'A' : 'a';
            text[i] = (char)(((ch - base + shift) % 26) + base);
        }
    }

    printf("Result: %s\n", text);
    return 0;
}
