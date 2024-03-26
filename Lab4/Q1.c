#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int arr[100];
    int i, max, sum = 0, count = 0;
    float avg;
   
    printf("Enter integers, one per line. Enter a non-integer to finish.\n");
    while (scanf("%d", &arr[count]) == 1) {
        sum += arr[count];
        if (count == 0 || arr[count] > max) {
            max = arr[count];
        }
        count++;
    }
   
    pid_t pid1, pid2, pid3;
    pid1 = fork();
   
    if (pid1 == 0) {
        printf("Sum = %d\n", sum);
    } else {
        pid2 = fork();
        if (pid2 == 0) {
            avg = (float)sum / count;
            printf("Average = %.2f\n", avg);
        } else {
            pid3 = fork();
            if (pid3 == 0) {
                printf("Maximum = %d\n", max);
            }
        }
    }
   
    for (i = 0; i < 3; i++) {
        wait(NULL);
    }
   
    return 0;
}
