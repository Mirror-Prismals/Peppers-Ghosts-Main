#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

static int bitap_search_exact(const char *text, const char *pattern) {
    size_t m = strlen(pattern);
    if (m == 0) {
        return 0;
    }
    if (m > 63) {
        fprintf(stderr, "Pattern too long (max 63 characters).\n");
        exit(1);
    }
    uint64_t mask[256] = {0};
    for (size_t i = 0; i < m; ++i) {
        mask[(unsigned char)pattern[i]] |= 1ULL << i;
    }
    uint64_t R = 0;
    uint64_t match_bit = 1ULL << (m - 1);
    for (size_t i = 0; text[i]; ++i) {
        R = ((R << 1) | 1ULL) & mask[(unsigned char)text[i]];
        if (R & match_bit) {
            return (int)(i - m + 1);
        }
    }
    return -1;
}

static int bitap_search_fuzzy(const char *text, const char *pattern, int k) {
    size_t m = strlen(pattern);
    if (m == 0) {
        return 0;
    }
    if (m > 63) {
        fprintf(stderr, "Pattern too long (max 63 characters).\n");
        exit(1);
    }
    uint64_t masks[256] = {0};
    for (size_t i = 0; i < m; ++i) {
        masks[(unsigned char)pattern[i]] |= 1ULL << i;
    }
    uint64_t VP = ~0ULL;
    uint64_t VN = 0;
    int curr = (int)m;
    uint64_t mask_bit = 1ULL << (m - 1);

    for (size_t i = 0; text[i]; ++i) {
        uint64_t PM = masks[(unsigned char)text[i]];
        uint64_t X = PM | VN;
        uint64_t D0 = (((X & VP) + VP) ^ VP) | X;
        uint64_t HP = VN | ~(D0 | VP);
        uint64_t HN = VP & D0;

        if (HP & mask_bit) {
            curr++;
        } else if (HN & mask_bit) {
            curr--;
        }

        if (curr <= k && i >= m - 1) {
            return (int)(i - m + 1);
        }

        VP = (HN << 1) | ~(D0 | ((HP << 1) | 1ULL));
        VN = D0 & ((HP << 1) | 1ULL);
    }
    return -1;
}

int main(void) {
    char text[1024];
    char pattern[256];
    int k;

    printf("Enter text: ");
    if (!fgets(text, sizeof(text), stdin)) {
        return 1;
    }
    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[--len] = '\0';
    }

    printf("Enter pattern: ");
    if (!fgets(pattern, sizeof(pattern), stdin)) {
        return 1;
    }
    len = strlen(pattern);
    if (len > 0 && pattern[len - 1] == '\n') {
        pattern[--len] = '\0';
    }

    printf("Enter max errors (-1 for exact search): ");
    if (scanf("%d", &k) != 1) {
        return 1;
    }

    int idx;
    if (k < 0) {
        idx = bitap_search_exact(text, pattern);
    } else {
        idx = bitap_search_fuzzy(text, pattern, k);
    }

    if (idx >= 0) {
        printf("Pattern found at index %d\n", idx);
    } else {
        printf("Pattern not found\n");
    }

    return 0;
}

