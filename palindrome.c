#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char str[256];
    printf("Enter a string: ");
    if (!fgets(str, sizeof(str), stdin)) {
        return 1;
    }

    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[--len] = '\0';
    }

    char clean[256];
    size_t j = 0;
    for (size_t i = 0; i < len; ++i) {
        if (isalnum((unsigned char)str[i])) {
            clean[j++] = (char)tolower((unsigned char)str[i]);
        }
    }
    clean[j] = '\0';

    size_t start = 0;
    size_t end = j ? j - 1 : 0;
    int is_palindrome = 1;
    while (start < end) {
        if (clean[start] != clean[end]) {
            is_palindrome = 0;
            break;
        }
        ++start;
        --end;
    }

    if (is_palindrome) {
        printf("\"%s\" is a palindrome.\n", str);
    } else {
        printf("\"%s\" is not a palindrome.\n", str);
    }

    return 0;
}

