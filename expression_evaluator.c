#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_EXPR_LEN 256

static int precedence(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

static int apply_op(int a, int b, char op, int *error) {
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0) {
            *error = 1;
            return 0;
        }
        return a / b;
    default:
        *error = 1;
        return 0;
    }
}

int main(void) {
    char expr[MAX_EXPR_LEN];
    printf("Enter an arithmetic expression: ");
    if (!fgets(expr, sizeof(expr), stdin)) {
        return 1;
    }

    size_t len = strlen(expr);
    if (len > 0 && expr[len - 1] == '\n') {
        expr[--len] = '\0';
    }

    int values[MAX_EXPR_LEN];
    char ops[MAX_EXPR_LEN];
    int val_top = -1, op_top = -1;

    for (size_t i = 0; i < len;) {
        if (isspace((unsigned char)expr[i])) {
            ++i;
            continue;
        }
        if (isdigit((unsigned char)expr[i])) {
            char *end;
            long val = strtol(&expr[i], &end, 10);
            values[++val_top] = (int)val;
            i = end - expr;
            continue;
        }
        if (expr[i] == '(') {
            ops[++op_top] = expr[i];
            ++i;
            continue;
        }
        if (expr[i] == ')') {
            while (op_top >= 0 && ops[op_top] != '(') {
                if (val_top < 1) {
                    fprintf(stderr, "Invalid expression.\n");
                    return 1;
                }
                int b = values[val_top--];
                int a = values[val_top--];
                int error = 0;
                int res = apply_op(a, b, ops[op_top--], &error);
                if (error) {
                    fprintf(stderr, "Error during evaluation.\n");
                    return 1;
                }
                values[++val_top] = res;
            }
            if (op_top < 0 || ops[op_top] != '(') {
                fprintf(stderr, "Mismatched parentheses.\n");
                return 1;
            }
            --op_top; // pop '('
            ++i;
            continue;
        }
        if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            while (op_top >= 0 && precedence(ops[op_top]) >= precedence(expr[i])) {
                if (val_top < 1) {
                    fprintf(stderr, "Invalid expression.\n");
                    return 1;
                }
                int b = values[val_top--];
                int a = values[val_top--];
                int error = 0;
                int res = apply_op(a, b, ops[op_top--], &error);
                if (error) {
                    fprintf(stderr, "Error during evaluation.\n");
                    return 1;
                }
                values[++val_top] = res;
            }
            ops[++op_top] = expr[i];
            ++i;
            continue;
        }
        fprintf(stderr, "Unknown character: %c\n", expr[i]);
        return 1;
    }

    while (op_top >= 0) {
        if (ops[op_top] == '(') {
            fprintf(stderr, "Mismatched parentheses.\n");
            return 1;
        }
        if (val_top < 1) {
            fprintf(stderr, "Invalid expression.\n");
            return 1;
        }
        int b = values[val_top--];
        int a = values[val_top--];
        int error = 0;
        int res = apply_op(a, b, ops[op_top--], &error);
        if (error) {
            fprintf(stderr, "Error during evaluation.\n");
            return 1;
        }
        values[++val_top] = res;
    }

    if (val_top != 0) {
        fprintf(stderr, "Invalid expression.\n");
        return 1;
    }

    printf("Result: %d\n", values[val_top]);
    return 0;
}

