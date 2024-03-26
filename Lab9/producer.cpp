#include <iostream>
#include <fstream>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

#define SHM_SIZE 20
#define SHM_KEY 1234
#define SEM_NAME "/mysemaphore"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    
    // Open the input file
    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Error: Failed to open file " << argv[1] << endl;
        return 1;
    }
    
    // Create shared memory segment
    int shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        return 1;
    }
    
    // Attach shared memory segment
    char *shmaddr = (char*) shmat(shmid, NULL, 0);
    if (shmaddr == (char*) -1) {
        perror("shmat");
        return 1;
    }
    
    // Create semaphore for synchronization
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }
    
    // Write to shared memory
    int i = 0;
    char c;
    while (input.get(c)) {
        sem_wait(sem);
        memcpy(shmaddr, &c, sizeof(char));
        shmaddr++;
        i++;
        if (i == SHM_SIZE) {
            sem_post(sem);
            while (*shmaddr != '\0') {
                usleep(10000);
            }
            shmaddr -= SHM_SIZE;
            i = 0;
        } else {
            sem_post(sem);
        }
    }
    
    // Write end-of-file marker to shared memory
    sem_wait(sem);
    *shmaddr = '$';
    sem_post(sem);
    
    // Wait for consumer to finish
    while (*shmaddr != '\0') {
        usleep(10000);
    }
    
    // Detach shared memory segment
    if (shmdt(shmaddr) < 0) {
        perror("shmdt");
        return 1;
    }
    
    // Delete shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) < 0) {
        perror("shmctl");
        return 1;
    }
    
    // Close semaphore
    if (sem_close(sem) < 0) {
        perror("sem_close");
        return 1;
    }
    
    // Delete semaphore
    if (sem_unlink(SEM_NAME) < 0) {
        perror("sem_unlink");
        return 1;
    }
    
    // Close input file
    input.close();
    
    return 0;
}
