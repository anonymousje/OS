#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int fibonacci_sequence(int n, int *sequence) {
    sequence[0] = 0;
    sequence[1] = 1;
    int i = 2;
    while (sequence[i - 1] < n) {
        sequence[i] = sequence[i - 1] + sequence[i - 2];
        i++;
    }
    return i;
}

void *generate_sequence(void *arg) {
    int term = *(int*)arg;
    int sequence[100];
    int length = fibonacci_sequence(term, sequence);
    printf("Thread %d: ", term);
    for (int i = 0; i < length; i++) {
        printf("%d", sequence[i]);
        if (i < length - 1) {
            printf(", ");
        }
    }
    printf("\n");
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int terms[argc - 1];
    for (int i = 1; i < argc; i++) {
        terms[i - 1] = atoi(argv[i]);
    }
    pthread_t threads[argc - 1];
    for (int i = 0; i < argc - 1; i++) {
        pthread_create(&threads[i], NULL, generate_sequence, &terms[i]);
    }
    for (int i = 0; i < argc - 1; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}

