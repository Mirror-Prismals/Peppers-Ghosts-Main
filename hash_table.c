#include <stdio.h>
#include <stdlib.h>

/* Simple hash table with separate chaining for integer key-value pairs */

typedef struct Entry {
    int key;
    int value;
    struct Entry *next;
} Entry;

typedef struct {
    Entry **buckets;
    int size;
} HashTable;

static unsigned int hash(int key, int size) {
    return (unsigned int)key % (unsigned int)size;
}

static HashTable *create_table(int size) {
    HashTable *t = malloc(sizeof(HashTable));
    if (!t) {
        return NULL;
    }
    t->buckets = calloc((size_t)size, sizeof(Entry *));
    if (!t->buckets) {
        free(t);
        return NULL;
    }
    t->size = size;
    return t;
}

static int insert(HashTable *t, int key, int value) {
    unsigned int idx = hash(key, t->size);
    Entry *e = t->buckets[idx];
    while (e) {
        if (e->key == key) {
            e->value = value;
            return 0;
        }
        e = e->next;
    }
    Entry *n = malloc(sizeof(Entry));
    if (!n) {
        return -1;
    }
    n->key = key;
    n->value = value;
    n->next = t->buckets[idx];
    t->buckets[idx] = n;
    return 0;
}

static int search(HashTable *t, int key, int *value) {
    unsigned int idx = hash(key, t->size);
    for (Entry *e = t->buckets[idx]; e; e = e->next) {
        if (e->key == key) {
            if (value) {
                *value = e->value;
            }
            return 1;
        }
    }
    return 0;
}

static int delete(HashTable *t, int key) {
    unsigned int idx = hash(key, t->size);
    Entry **cur = &t->buckets[idx];
    while (*cur) {
        if ((*cur)->key == key) {
            Entry *tmp = *cur;
            *cur = tmp->next;
            free(tmp);
            return 1;
        }
        cur = &(*cur)->next;
    }
    return 0;
}

static void print_table(const HashTable *t) {
    for (int i = 0; i < t->size; ++i) {
        printf("Bucket %d:", i);
        for (Entry *e = t->buckets[i]; e; e = e->next) {
            printf(" (%d:%d)", e->key, e->value);
        }
        putchar('\n');
    }
}

static void free_table(HashTable *t) {
    if (t) {
        for (int i = 0; i < t->size; ++i) {
            Entry *e = t->buckets[i];
            while (e) {
                Entry *tmp = e->next;
                free(e);
                e = tmp;
            }
        }
        free(t->buckets);
        free(t);
    }
}

int main(void) {
    int size;
    printf("Enter hash table size: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        fprintf(stderr, "Invalid size.\n");
        return 1;
    }
    HashTable *t = create_table(size);
    if (!t) {
        perror("create_table");
        return 1;
    }
    int n;
    printf("Enter number of key-value pairs: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid count.\n");
        free_table(t);
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        int key, value;
        printf("Pair %d (key value): ", i + 1);
        if (scanf("%d %d", &key, &value) != 2) {
            fprintf(stderr, "Invalid input.\n");
            free_table(t);
            return 1;
        }
        if (insert(t, key, value) != 0) {
            perror("insert");
            free_table(t);
            return 1;
        }
    }

    printf("Current table:\n");
    print_table(t);

    int key;
    printf("Enter key to search: ");
    if (scanf("%d", &key) != 1) {
        fprintf(stderr, "Invalid input.\n");
        free_table(t);
        return 1;
    }
    int value;
    if (search(t, key, &value)) {
        printf("Found: %d -> %d\n", key, value);
    } else {
        printf("%d not found.\n", key);
    }

    printf("Enter key to delete: ");
    if (scanf("%d", &key) != 1) {
        fprintf(stderr, "Invalid input.\n");
        free_table(t);
        return 1;
    }
    if (delete(t, key)) {
        printf("%d deleted.\n", key);
    } else {
        printf("%d not found.\n", key);
    }

    printf("Table after deletion:\n");
    print_table(t);

    free_table(t);
    return 0;
}

