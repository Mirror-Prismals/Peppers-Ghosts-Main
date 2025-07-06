#include <stdio.h>
#include <string.h>

struct roman_map {
    int value;
    const char *numeral;
};

static const struct roman_map map[] = {
    {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
    {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
    {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
};

int main(void) {
    int num;
    printf("Enter an integer (1-3999): ");
    if (scanf("%d", &num) != 1 || num <= 0 || num > 3999) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    char result[64] = "";
    char *p = result;
    for (size_t i = 0; i < sizeof(map) / sizeof(map[0]); ++i) {
        while (num >= map[i].value) {
            strcpy(p, map[i].numeral);
            p += strlen(map[i].numeral);
            num -= map[i].value;
        }
    }
    printf("Roman numeral: %s\n", result);
    return 0;
}
