#include <stdio.h>
#include <string.h>

static int expand(const char *s, int left, int right, int n) {
    while (left >= 0 && right < n && s[left] == s[right]) {
        --left;
        ++right;
    }
    return right - left - 1; /* length of palindrome */
}

int main(void) {
    char str[1024];
    printf("Enter a string: ");
    if (!fgets(str, sizeof(str), stdin)) {
        return 1;
    }
    size_t n = strlen(str);
    if (n > 0 && str[n - 1] == '\n') {
        str[--n] = '\0';
    }

    if (n == 0) {
        printf("Longest palindromic substring: \nLength: 0\n");
        return 0;
    }

    int start = 0;
    int end = 0;
    for (int i = 0; i < (int)n; ++i) {
        int len1 = expand(str, i, i, n);
        int len2 = expand(str, i, i + 1, n);
        int len = len1 > len2 ? len1 : len2;
        if (len > end - start + 1) {
            start = i - (len - 1) / 2;
            end = i + len / 2;
        }
    }

    int length = end - start + 1;
    char result[1024];
    memcpy(result, str + start, length);
    result[length] = '\0';

    printf("Longest palindromic substring: %s\n", result);
    printf("Length: %d\n", length);
    return 0;
}
