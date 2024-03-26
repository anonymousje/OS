#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define PIPE_NAME "mynamedpipe"

int main() {
    int pipe_fd = open(PIPE_NAME, O_RDONLY);
    if (pipe_fd == -1) {
        perror("open");
        exit(1);
    }
    printf("Client started\n");
    while (1) {
        printf("Enter operator and operands separated by spaces (or \"quit\" to exit): ");
        char buffer[100];
        if (fgets(buffer, 100, stdin) == NULL) {
            break;
        }
        if (strcmp(buffer, "quit\n") == 0) {
            break;
        }
        write(pipe_fd, buffer, strlen(buffer));
        double result;
        read(pipe_fd, &result, sizeof(double));
        printf("Result: %lf\n", result);
    }
    close(pipe_fd);
    printf("Client stopped\n");
    return 0;
}
