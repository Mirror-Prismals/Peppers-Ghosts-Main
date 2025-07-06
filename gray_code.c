#include <stdio.h>

static void print_binary(unsigned int num, unsigned int bits) {
    for (int i = (int)bits - 1; i >= 0; --i) {
        putchar((num & (1u << i)) ? '1' : '0');
    }
}

int main(void) {
    unsigned int n;
    printf("Enter the number of bits (1-16): ");
    if (scanf("%u", &n) != 1 || n == 0 || n > 16) {
        fprintf(stderr, "Invalid number of bits.\n");
        return 1;
    }
    unsigned int total = 1u << n;
    for (unsigned int i = 0; i < total; ++i) {
        unsigned int gray = i ^ (i >> 1);
        print_binary(gray, n);
        putchar('\n');
    }
    return 0;
}
