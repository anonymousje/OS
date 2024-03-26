#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>

#define PIPE_NAME "mynamedpipe"

void handler(int signum) {
    if (signum == SIGPIPE) {
        printf("Client has disconnected\n");
    }
    exit(0);
}

int main() {
    signal(SIGPIPE, handler);
    if (mkfifo(PIPE_NAME, 0666) == -1) {
        if (errno != EEXIST) {
            perror("mkfifo");
            exit(1);
        }
    }
    int pipe_fd = open(PIPE_NAME, O_WRONLY);
    printf("Server started\n");
    while (1) {
        char buffer[100];
        if (read(STDIN_FILENO, buffer, 100) <= 0) {
            break;
        }
        if (strcmp(buffer, "quit\n") == 0) {
            break;
        }
        write(pipe_fd, buffer, strlen(buffer));
        double operand1, operand2, result;
        char operator;
        read(pipe_fd, &operator, 1);
        read(pipe_fd, &operand1, sizeof(double));
        read(pipe_fd, &operand2, sizeof(double));
        switch (operator) {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                result = operand1 / operand2;
                break;
            default:
                result = 0.0;
        }
        printf("Result: %lf\n", result);
    }
    close(pipe_fd);
    unlink(PIPE_NAME);
    printf("Server stopped\n");
    return 0;
}
