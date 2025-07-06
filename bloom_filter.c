#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Simple Bloom filter for strings using two hash functions */

typedef struct {
    unsigned char *bits;
    unsigned int size; /* number of bits */
} BloomFilter;

static unsigned int hash1(const char *s, unsigned int m) {
    unsigned int h = 2166136261u; /* FNV-1a */
    while (*s) {
        h ^= (unsigned char)*s++;
        h *= 16777619u;
    }
    return h % m;
}

static unsigned int hash2(const char *s, unsigned int m) {
    unsigned int h = 5381u; /* djb2 */
    while (*s) {
        h = ((h << 5) + h) + (unsigned char)*s++;
    }
    return h % m;
}

static void set_bit(unsigned char *bits, unsigned int pos) {
    bits[pos / 8u] |= (unsigned char)(1u << (pos % 8u));
}

static int get_bit(const unsigned char *bits, unsigned int pos) {
    return (bits[pos / 8u] >> (pos % 8u)) & 1u;
}

static int bloom_init(BloomFilter *b, unsigned int size) {
    b->bits = calloc((size + 7u) / 8u, 1);
    if (!b->bits) {
        return -1;
    }
    b->size = size;
    return 0;
}

static void bloom_add(BloomFilter *b, const char *s) {
    unsigned int h1 = hash1(s, b->size);
    unsigned int h2 = hash2(s, b->size);
    set_bit(b->bits, h1);
    set_bit(b->bits, h2);
}

static int bloom_check(BloomFilter *b, const char *s) {
    unsigned int h1 = hash1(s, b->size);
    unsigned int h2 = hash2(s, b->size);
    return get_bit(b->bits, h1) && get_bit(b->bits, h2);
}

static void bloom_free(BloomFilter *b) {
    free(b->bits);
}

int main(void) {
    unsigned int size;
    printf("Enter Bloom filter size in bits: ");
    if (scanf("%u", &size) != 1 || size == 0u) {
        fprintf(stderr, "Invalid size.\n");
        return 1;
    }
    BloomFilter b;
    if (bloom_init(&b, size) != 0) {
        perror("calloc");
        return 1;
    }

    int n;
    printf("Enter number of words to add: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid count.\n");
        bloom_free(&b);
        return 1;
    }
    char word[101];
    for (int i = 0; i < n; ++i) {
        printf("Word %d: ", i + 1);
        if (scanf("%100s", word) != 1) {
            fprintf(stderr, "Invalid input.\n");
            bloom_free(&b);
            return 1;
        }
        bloom_add(&b, word);
    }

    int q;
    printf("Enter number of queries: ");
    if (scanf("%d", &q) != 1 || q < 0) {
        fprintf(stderr, "Invalid count.\n");
        bloom_free(&b);
        return 1;
    }
    for (int i = 0; i < q; ++i) {
        printf("Query %d: ", i + 1);
        if (scanf("%100s", word) != 1) {
            fprintf(stderr, "Invalid input.\n");
            bloom_free(&b);
            return 1;
        }
        if (bloom_check(&b, word)) {
            printf("'%s' may be present.\n", word);
        } else {
            printf("'%s' not present.\n", word);
        }
    }

    bloom_free(&b);
    return 0;
}

