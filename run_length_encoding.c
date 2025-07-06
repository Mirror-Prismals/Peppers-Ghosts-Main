#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void rle_encode(const char *input, char *output) {
    size_t j = 0;
    for (size_t i = 0; input[i] != '\0';) {
        char current = input[i];
        size_t count = 1;
        while (input[i + count] == current) {
            ++count;
        }
        j += sprintf(output + j, "%zu%c", count, current);
        i += count;
    }
    output[j] = '\0';
}

static size_t rle_decoded_length(const char *input) {
    size_t length = 0;
    size_t count = 0;
    for (size_t i = 0; input[i] != '\0'; ++i) {
        if (isdigit((unsigned char)input[i])) {
            count = count * 10 + (input[i] - '0');
        } else {
            length += count;
            count = 0;
        }
    }
    return length;
}

static void rle_decode(const char *input, char *output) {
    size_t j = 0;
    size_t count = 0;
    for (size_t i = 0; input[i] != '\0'; ++i) {
        if (isdigit((unsigned char)input[i])) {
            count = count * 10 + (input[i] - '0');
        } else {
            for (size_t k = 0; k < count; ++k) {
                output[j++] = input[i];
            }
            count = 0;
        }
    }
    output[j] = '\0';
}

int main(void) {
    char mode;
    printf("Encode or decode? (e/d): ");
    if (scanf(" %c", &mode) != 1 || (mode != 'e' && mode != 'd')) {
        fprintf(stderr, "Invalid mode.\n");
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

    if (mode == 'e') {
        char *encoded = malloc(2 * len + 1);
        if (!encoded) {
            perror("malloc");
            return 1;
        }
        rle_encode(text, encoded);
        printf("Encoded: %s\n", encoded);
        free(encoded);
    } else {
        size_t out_len = rle_decoded_length(text);
        char *decoded = malloc(out_len + 1);
        if (!decoded) {
            perror("malloc");
            return 1;
        }
        rle_decode(text, decoded);
        printf("Decoded: %s\n", decoded);
        free(decoded);
    }
    return 0;
}

