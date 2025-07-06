#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_matching(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

static int is_balanced(const char *str) {
    size_t len = strlen(str);
    char *stack = malloc(len);
    if (!stack) {
        return -1; // allocation failure
    }
    size_t top = 0;
    for (size_t i = 0; str[i] != '\0'; ++i) {
        char c = str[i];
        if (c == '(' || c == '[' || c == '{') {
            stack[top++] = c;
        } else if (c == ')' || c == ']' || c == '}') {
            if (top == 0 || !is_matching(stack[top - 1], c)) {
                free(stack);
                return 0; // not balanced
            }
            --top;
        }
    }
    int balanced = (top == 0);
    free(stack);
    return balanced;
}

int main(void) {
    char input[1024];
    printf("Enter text with parentheses: ");
    if (!fgets(input, sizeof(input), stdin)) {
        return 1;
    }
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    int result = is_balanced(input);
    if (result < 0) {
        perror("malloc");
        return 1;
    }
    printf(result ? "Balanced\n" : "Not balanced\n");
    return 0;
}
