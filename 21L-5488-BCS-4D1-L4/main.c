#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>


int main() {
    
    int fd[2], fd2[2];
    pipe(fd);
    pipe(fd2);

    
    pid_t pid = fork();

    if (pid == 0) {
       
        close(fd[1]);

        char message[1024];
        read(fd[0], message, 1024);
		
		int i = 0;
        while(i < sizeof(message))
         {
            if (islower(message[i])) 
            {
                message[i] = toupper(message[i]);
                
            } 
            else if (isupper(message[i]))
             {
                message[i] = tolower(message[i]);
            }
            i++;
        }
        

        
        close(fd2[0]);

        
        write(fd2[1], message, strlen(message)+1);

    } else {
        

        
        close(fd[0]);

        
        char message[] = "Hi There";
        write(fd[1], message, strlen(message)+1);

        
        close(fd2[1]);

        
        char modified_message[1024];
        read(fd2[0], modified_message, 1024);

        
        printf("%s\n", modified_message);
        
    }

    return 0;
}
