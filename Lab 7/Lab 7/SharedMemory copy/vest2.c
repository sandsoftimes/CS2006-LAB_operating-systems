#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

#define SHM_KEY 1234
#define SEM_KEY 5678

int main() {
    // Create shared memory segment
    int shmid = shmget(SHM_KEY, 1024, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach shared memory segment
    char* shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char*)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Create semaphore
    int semid = semget(SEM_KEY, 2, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Initialize semaphore values
    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    } arg;
    arg.val = 0;
    semctl(semid, 0, SETVAL, arg); // semaphore 0: B and C not completed yet
    arg.val = 0;
    semctl(semid, 1, SETVAL, arg); // semaphore 1: A waiting for B and C to complete

    pid_t pidB = fork();
    if (pidB == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pidB == 0) { // Process B
        printf("Process B writing to shared memory...\n");
        sprintf(shmaddr, "shared");

        // Signal A and C that B has completed
        struct sembuf ops[] = {
            { .sem_num = 0, .sem_op = 1 }, // semaphore 0: B has completed
            { .sem_num = 1, .sem_op = 1 }, // semaphore 1: A can proceed
        };
        semop(semid, ops, 2);

        exit(EXIT_SUCCESS);
    }

    pid_t pidC = fork();
    if (pidC == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pidC == 0) { // Process C
        printf("Process C writing to shared memory...\n");

        // Wait for B to complete
        struct sembuf ops[] = {
            { .sem_num = 0, .sem_op = -1 }, // semaphore 0: B not completed yet
        };
        semop(semid, ops, 1);

        sprintf(shmaddr, "memory");

        // Signal A that C has completed
        ops[0].sem_op = 1; // semaphore 0: not needed anymore
        ops[1].sem_op = 1; // semaphore 1: A can proceed
        semop(semid, ops, 2);

        exit(EXIT_SUCCESS);
    }

    // Process A
    printf("Process A writing to shared memory and waiting...\n");
    sprintf(shmaddr, "waiting");

    // Wait for B and C to complete
    struct sembuf ops[] = {
        { .sem_num = 1, .sem_op = -1 }, // semaphore 1: A waits for B and C to complete
    };
    semop(semid, ops, 1);

    printf("Process A reading from shared memory: %s\n");
    }
