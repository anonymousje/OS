#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  // Open the file for writing
  FILE *file = fopen("myfile.txt", "w");
  if (file == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  // Redirect stdout to the file
  int fd = fileno(file);
  if (dup2(fd, STDOUT_FILENO) == -1) {
    perror("dup2");
    exit(EXIT_FAILURE);
  }

  // Execute the ls command
  execlp("ls", "ls", NULL);

  // If we reach here, the execlp call failed
  perror("execlp");
  exit(EXIT_FAILURE);
}
