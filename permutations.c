#include <stdio.h>
#include <string.h>

static void swap(char *x, char *y) {
    char tmp = *x;
    *x = *y;
    *y = tmp;
}

static void permute(char *str, int l, int r) {
    if (l == r) {
        printf("%s\n", str);
        return;
    }
    for (int i = l; i <= r; ++i) {
        swap(&str[l], &str[i]);
        permute(str, l + 1, r);
        swap(&str[l], &str[i]);
    }
}

int main(void) {
    char input[100];
    printf("Enter a string: ");
    if (scanf("%99s", input) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    size_t len = strlen(input);
    if (len == 0) {
        return 0;
    }
    permute(input, 0, (int)len - 1);
    return 0;
}
