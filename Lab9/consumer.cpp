#include <iostream>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <cstring>

using namespace std;

int main() {
    // Initialize semaphore
    sem_t* semaphore = sem_open("/my_semaphore", O_CREAT, 0666, 0);
    if (semaphore == SEM_FAILED) {
        perror("Failed to open semaphore");
        exit(1);
    }
    
    // Get shared memory id
    key_t key = ftok("shared_memory", 'a');
    int shmid = shmget(key, 20, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("Failed to get shared memory id");
        exit(1);
    }
    
    // Attach shared memory
    char* shared_memory = (char*) shmat(shmid, NULL, 0);
    if (shared_memory == (char*) -1) {
        perror("Failed to attach shared memory");
        exit(1);
    }
    
    // Print shared memory contents and wait for user input
    bool end_of_file = false;
    while (!end_of_file) {
        // Wait for producer to write to shared memory
        sem_wait(semaphore);
        
        // Print shared memory contents
        cout << shared_memory << endl;
        
        // Check for end of file
        if (shared_memory[0] == '$') {
            end_of_file = true;
        }
        
        // Clear shared memory
        memset(shared_memory, 0, 20);
        
        // Signal producer to write to shared memory
        sem_post(semaphore);
        
        // Wait for user input
        getchar();
    }
    
    // Detach shared memory
    if (shmdt(shared_memory) == -1) {
        perror("Failed to detach shared memory");
        exit(1);
    }
    
    // Delete shared memory
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("Failed to delete shared memory");
        exit(1);
    }
    
    // Close semaphore
    if (sem_close(semaphore) == -1) {
        perror("Failed to close semaphore");
        exit(1);
    }
    
    return 0;
}
