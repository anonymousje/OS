#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


double calculate_average(int* numbers, int count) {
    double sum = 0;
    int i = 1;
    while (i < count +1) {
        sum += numbers[i];
        i++;
    }
    return sum / (double)count;
}

int calculate_maximum(int* numbers, int count) {
    int max = numbers[0];
    int i = 1;
    while (i < count) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
        i++;
    }
    return max;
}

int calculate_minimum(int* numbers, int count) {
    int min = numbers[0];
    int i = 1;
    while (i < count) {
        if (numbers[i] < min) {
            min = numbers[i];
        }
        i++;
    }
    return min;
}


void* average_thread(void* arg) {
    int* numbers = (int*)arg;
    double* result = (double*)malloc(sizeof(double));
    *result = calculate_average(numbers, numbers[0]);
    pthread_exit(result);
}

void* maximum_thread(void* arg) {
    int* numbers = (int*)arg;
    int* result = (int*)malloc(sizeof(int));
    *result = calculate_maximum(numbers + 1, numbers[0]);
    pthread_exit(result);
}

void* minimum_thread(void* arg) {
    int* numbers = (int*)arg;
    int* result = (int*)malloc(sizeof(int));
    *result = calculate_minimum(numbers + 1, numbers[0]);
    pthread_exit(result);
}

int main(int argc, char* argv[]) {
    int count = argc - 1;
    int* numbers = (int*)malloc(sizeof(int) * (count + 1));
    numbers[0] = count;
    int i = 1;
    while (i <= count) {
        numbers[i] = atoi(argv[i]);
        i++;
    }
    

    
    pthread_t threads[3];
    double* average_result;
    int* maximum_result;
    int* minimum_result;
    pthread_create(&threads[0], NULL, average_thread, numbers);
    pthread_create(&threads[1], NULL, maximum_thread, numbers);
    pthread_create(&threads[2], NULL, minimum_thread, numbers);

    
    pthread_join(threads[0], (void**)&average_result);
    pthread_join(threads[1], (void**)&maximum_result);
    pthread_join(threads[2], (void**)&minimum_result);

    
    printf("Average: %.2f\n", *average_result);
    printf("Maximum: %d\n", *maximum_result);
    printf("Minimum: %d\n", *minimum_result);

    
    free(numbers);
    free(average_result);
    free(maximum_result);
    free(minimum_result);

    return 0;
}


