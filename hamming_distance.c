#include <stdio.h>
#include <string.h>

int main(void) {
    char s1[1024];
    char s2[1024];

    printf("Enter first string: ");
    if (!fgets(s1, sizeof(s1), stdin)) {
        return 1;
    }
    printf("Enter second string: ");
    if (!fgets(s2, sizeof(s2), stdin)) {
        return 1;
    }

    size_t len1 = strlen(s1);
    if (len1 > 0 && s1[len1 - 1] == '\n') {
        s1[--len1] = '\0';
    }
    size_t len2 = strlen(s2);
    if (len2 > 0 && s2[len2 - 1] == '\n') {
        s2[--len2] = '\0';
    }

    if (len1 != len2) {
        fprintf(stderr, "Strings must be of equal length.\n");
        return 1;
    }

    int distance = 0;
    for (size_t i = 0; i < len1; ++i) {
        if (s1[i] != s2[i]) {
            ++distance;
        }
    }

    printf("Hamming distance: %d\n", distance);
    return 0;
}
