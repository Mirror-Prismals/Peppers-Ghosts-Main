#include <stdio.h>
#include <string.h>

static int is_matching(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

static int is_balanced(const char *expr) {
    char stack[1024];
    int top = -1;
    for (size_t i = 0; expr[i]; ++i) {
        char ch = expr[i];
        if (ch == '(' || ch == '[' || ch == '{') {
            if (top >= (int)(sizeof(stack) / sizeof(stack[0])) - 1) {
                return 0; // stack overflow
            }
            stack[++top] = ch;
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (top < 0 || !is_matching(stack[top--], ch)) {
                return 0;
            }
        }
    }
    return top == -1;
}

int main(void) {
    char expr[1024];
    printf("Enter an expression: ");
    if (!fgets(expr, sizeof(expr), stdin)) {
        return 1;
    }
    size_t len = strlen(expr);
    if (len > 0 && expr[len - 1] == '\n') {
        expr[len - 1] = '\0';
    }

    if (is_balanced(expr)) {
        printf("The expression has balanced parentheses.\n");
    } else {
        printf("The expression does not have balanced parentheses.\n");
    }
    return 0;
}
