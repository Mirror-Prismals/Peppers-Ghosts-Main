#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 6
#define P 0.5

typedef struct Node {
    int value;
    struct Node *forward[MAX_LEVEL];
} Node;

typedef struct {
    Node *header;
    int level;
} SkipList;

static Node *create_node(int value) {
    Node *n = malloc(sizeof(Node));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->value = value;
    for (int i = 0; i < MAX_LEVEL; ++i) {
        n->forward[i] = NULL;
    }
    return n;
}

static SkipList *create_list(void) {
    SkipList *list = malloc(sizeof(SkipList));
    if (!list) {
        perror("malloc");
        exit(1);
    }
    list->level = 0;
    list->header = create_node(0); /* header node value unused */
    return list;
}

static int random_level(void) {
    int lvl = 0;
    while ((double)rand() / RAND_MAX < P && lvl < MAX_LEVEL - 1) {
        ++lvl;
    }
    return lvl;
}

static void insert(SkipList *list, int value) {
    Node *update[MAX_LEVEL];
    Node *x = list->header;
    for (int i = list->level; i >= 0; --i) {
        while (x->forward[i] && x->forward[i]->value < value) {
            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[0];
    if (x && x->value == value) {
        return; /* no duplicates */
    }
    int lvl = random_level();
    if (lvl > list->level) {
        for (int i = list->level + 1; i <= lvl; ++i) {
            update[i] = list->header;
        }
        list->level = lvl;
    }
    x = create_node(value);
    for (int i = 0; i <= lvl; ++i) {
        x->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = x;
    }
}

static Node *search(SkipList *list, int value) {
    Node *x = list->header;
    for (int i = list->level; i >= 0; --i) {
        while (x->forward[i] && x->forward[i]->value < value) {
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    if (x && x->value == value) {
        return x;
    }
    return NULL;
}

static void delete(SkipList *list, int value) {
    Node *update[MAX_LEVEL];
    Node *x = list->header;
    for (int i = list->level; i >= 0; --i) {
        while (x->forward[i] && x->forward[i]->value < value) {
            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[0];
    if (!x || x->value != value) {
        return; /* not found */
    }
    for (int i = 0; i <= list->level; ++i) {
        if (update[i]->forward[i] != x) {
            break;
        }
        update[i]->forward[i] = x->forward[i];
    }
    free(x);
    while (list->level > 0 && !list->header->forward[list->level]) {
        --list->level;
    }
}

static void print_list(SkipList *list) {
    printf("Elements: ");
    Node *x = list->header->forward[0];
    while (x) {
        printf("%d ", x->value);
        x = x->forward[0];
    }
    printf("\n");
}

static void free_list(SkipList *list) {
    Node *x = list->header;
    while (x) {
        Node *next = x->forward[0];
        free(x);
        x = next;
    }
    free(list);
}

int main(void) {
    srand((unsigned)time(NULL));
    int n;
    printf("Enter number of integers: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    SkipList *list = create_list();
    for (int i = 0; i < n; ++i) {
        int value;
        if (scanf("%d", &value) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free_list(list);
            return 1;
        }
        insert(list, value);
    }
    print_list(list);
    int key;
    printf("Enter value to search: ");
    if (scanf("%d", &key) != 1) {
        fprintf(stderr, "Invalid input.\n");
        free_list(list);
        return 1;
    }
    if (search(list, key)) {
        printf("%d found in the list.\n", key);
    } else {
        printf("%d not found in the list.\n", key);
    }
    printf("Enter value to delete: ");
    if (scanf("%d", &key) != 1) {
        fprintf(stderr, "Invalid input.\n");
        free_list(list);
        return 1;
    }
    delete(list, key);
    print_list(list);
    free_list(list);
    return 0;
}

