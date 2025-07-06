#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 256

static void build_bad_char_table(const char *pat, int m, int bad_char[ALPHABET_SIZE]) {
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        bad_char[i] = -1;
    }
    for (int i = 0; i < m; ++i) {
        bad_char[(unsigned char)pat[i]] = i;
    }
}

static int boyer_moore_search(const char *text, const char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    if (m == 0) {
        return 0;
    }
    int bad_char[ALPHABET_SIZE];
    build_bad_char_table(pattern, m, bad_char);
    int shift = 0;
    while (shift <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[shift + j]) {
            --j;
        }
        if (j < 0) {
            return shift;
        }
        int bad_index = bad_char[(unsigned char)text[shift + j]];
        int skip = j - bad_index;
        if (skip < 1) {
            skip = 1;
        }
        shift += skip;
    }
    return -1;
}

int main(void) {
    char text[1024];
    char pattern[1024];
    printf("Enter text: ");
    if (!fgets(text, sizeof(text), stdin)) {
        return 1;
    }
    text[strcspn(text, "\n")] = '\0';
    printf("Enter pattern: ");
    if (!fgets(pattern, sizeof(pattern), stdin)) {
        return 1;
    }
    pattern[strcspn(pattern, "\n")] = '\0';
    int index = boyer_moore_search(text, pattern);
    if (index >= 0) {
        printf("Pattern found at index %d\n", index);
    } else {
        printf("Pattern not found\n");
    }
    return 0;
}

