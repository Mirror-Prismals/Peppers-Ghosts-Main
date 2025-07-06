#include <stdio.h>
#include <string.h>

static int expand_around_center(const char *s, int left, int right) {
    int n = (int)strlen(s);
    while (left >= 0 && right < n && s[left] == s[right]) {
        --left;
        ++right;
    }
    return right - left - 1;
}

int main(void) {
    char str[1024];
    printf("Enter a string: ");
    if (!fgets(str, sizeof(str), stdin)) {
        return 1;
    }
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[--len] = '\0';
    }

    int start = 0;
    int max_len = 1;

    for (int i = 0; i < (int)len; ++i) {
        int len1 = expand_around_center(str, i, i);
        int len2 = expand_around_center(str, i, i + 1);
        int cur_len = len1 > len2 ? len1 : len2;
        if (cur_len > max_len) {
            max_len = cur_len;
            start = i - (max_len - 1) / 2;
        }
    }

    printf("Longest palindromic substring: %.*s\n", max_len, str + start);
    return 0;
}
