#include <stdio.h>

static int roman_value(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

static int roman_to_int(const char *s) {
    int total = 0;
    for (int i = 0; s[i]; ++i) {
        int curr = roman_value(s[i]);
        if (curr == 0) {
            return -1;  // invalid character
        }
        int next = roman_value(s[i + 1]);
        if (next > curr) {
            total += next - curr;
            ++i;  // skip next character
        } else {
            total += curr;
        }
    }
    return total;
}

int main(void) {
    char input[100];
    printf("Enter a Roman numeral (uppercase): ");
    if (scanf("%99s", input) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    int value = roman_to_int(input);
    if (value < 0) {
        fprintf(stderr, "Invalid Roman numeral.\n");
        return 1;
    }
    printf("%s = %d\n", input, value);
    return 0;
}
