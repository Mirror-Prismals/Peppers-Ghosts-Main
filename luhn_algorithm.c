#include <stdio.h>
#include <string.h>

static int luhn_check(const char *number) {
    int sum = 0;
    size_t len = strlen(number);
    int double_digit = 0;

    for (int i = (int)len - 1; i >= 0; --i) {
        char c = number[i];
        if (c < '0' || c > '9') {
            return 0; // invalid character
        }
        int digit = c - '0';
        if (double_digit) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9;
            }
        }
        sum += digit;
        double_digit = !double_digit;
    }
    return sum % 10 == 0;
}

int main(void) {
    char number[256];
    printf("Enter a number to validate with the Luhn algorithm: ");
    if (scanf("%255s", number) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    if (luhn_check(number)) {
        printf("%s is valid.\n", number);
    } else {
        printf("%s is invalid.\n", number);
    }
    return 0;
}
