#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main()
{
    int shmid;
    key_t key;
    char *shm;
    char *s;

    // create a key for the shared memory segment
    key = ftok("shmfile", 'R');

    // create the shared memory segment
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // attach the shared memory segment to our data space
    shm = shmat(shmid, NULL, 0);

    if (shm == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // process A writes to position 1 in memory and then waits until B and C completes
    shm[0] = 'A';
    while (shm[1] != 'B' || shm[2] != 'C') {
        sleep(1);
    }

    // print the strings written by B and C
    printf("Process A: %s%s\n", shm+3, shm+8);

    // detach the shared memory segment from our data space
    if (shmdt(shm) == -1) {
        perror("shmdt");
        exit(1);
    }

    // delete the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    return 0;
}

