#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Reservoir sampling: select k items uniformly at random from a stream of
 * unknown length. This implementation reads integers from standard input until
 * EOF is reached and outputs a random sample of k of them.
 */

int main(void) {
    int k;
    printf("Enter sample size k: ");
    if (scanf("%d", &k) != 1 || k <= 0) {
        fprintf(stderr, "Invalid sample size.\n");
        return 1;
    }

    int *reservoir = malloc(k * sizeof(int));
    if (!reservoir) {
        perror("malloc");
        return 1;
    }

    int value;
    int count = 0; /* number of items seen so far */

    /* Fill the reservoir with the first k items */
    while (count < k && scanf("%d", &value) == 1) {
        reservoir[count++] = value;
    }

    if (count < k) {
        printf("Stream contained fewer than %d items.\n", k);
        for (int i = 0; i < count; ++i) {
            printf("%d\n", reservoir[i]);
        }
        free(reservoir);
        return 0;
    }

    srand((unsigned)time(NULL));
    /* Process remaining items */
    while (scanf("%d", &value) == 1) {
        ++count;
        int j = rand() % count; /* j is between 0 and count - 1 */
        if (j < k) {
            reservoir[j] = value;
        }
    }

    printf("Sampled items:\n");
    for (int i = 0; i < k; ++i) {
        printf("%d\n", reservoir[i]);
    }

    free(reservoir);
    return 0;
}

