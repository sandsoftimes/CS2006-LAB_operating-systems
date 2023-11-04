#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define SHMSIZE 1024

int main() {
    int shmid;
    char *shmaddr;
    key_t key = ftok(".", 'x');

    // create shared memory segment
    shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // attach shared memory segment to process address space
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // initialize shared memory position 0 to 0
    shmaddr[0] = '0';

    // fork process B
    pid_t pid_b = fork();
    if (pid_b == -1) {
        perror("fork");
        exit(1);
    } else if (pid_b == 0) {
        // process B
        while (shmaddr[0] == '0') ; // busy wait for process A to write to shared memory
        strcpy(shmaddr+1, "shared");
        shmaddr[0] = '1';
        exit(0);
    }

    // fork process C
    pid_t pid_c = fork();
    if (pid_c == -1) {
        perror("fork");
        exit(1);
    } else if (pid_c == 0) {
        // process C
        while (shmaddr[0] == '1') ; // busy wait for process B to write to shared memory
        strcpy(shmaddr+8, "memory");
        shmaddr[5] = ' ';
        shmaddr[0] = '2';
        exit(0);
    }

    // process A
    while (shmaddr[0] < '1') ; // busy wait for both processes B and C to write to shared memory
    printf("%s\n", shmaddr+1);

    // wait for both child processes to finish writing to shared memory
    waitpid(pid_b, NULL, 0);
    waitpid(pid_c, NULL, 0);

    // print the contents of shared memory again
    printf("%s\n", shmaddr+8);

    // detach and remove shared memory segment
    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}