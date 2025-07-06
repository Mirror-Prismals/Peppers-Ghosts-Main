#include <stdio.h>
#include <string.h>

static void reverse(char *str) {
    size_t len = strlen(str);
    if (len == 0) {
        return;
    }
    for (size_t i = 0, j = len - 1; i < j; ++i, --j) {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}

int main(void) {
    char buffer[1024];
    printf("Enter a string: ");
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return 1;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    reverse(buffer);
    printf("Reversed string: %s\n", buffer);
    return 0;
}
