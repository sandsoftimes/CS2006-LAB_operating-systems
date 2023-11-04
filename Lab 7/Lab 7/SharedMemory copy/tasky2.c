#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main()
{
    int shmid;
    key_t key;
    int *shm, *s;
    int arr[5] = {1, 2, 3, 4, 5};

    /* create a key for the shared memory segment */
    if ((key = ftok(".", 'A')) == -1) {
        perror("ftok");
        exit(1);
    }

    /* create the shared memory segment */
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) == -1) {
        perror("shmget");
        exit(1);
    }

    /* attach the shared memory segment */
    if ((shm = shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    /* write the array of integers to the shared memory segment from the parent process */
    s = shm;
    for (int i = 0; i < 5; i++) {
        *s++ = arr[i];
    }

    /* fork a child process */
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    /* child process */
    else if (pid == 0) {
        /* read the array of integers from the shared memory segment */
        s = shm;
        int result = 0;
        for (int i = 0; i < 5; i++) {
            result += *s++;
        }

        /* perform a series of operations on the array */
        result *= 2;

        /* write the result back to the shared memory segment */
        s = shm;
        *s = result;

        /* detach the shared memory segment */
        if (shmdt(shm) == -1) {
            perror("shmdt");
            exit(1);
        }

        exit(0);
    }

    /* parent process */
    else {
        /* wait for the child process to finish */
        wait(NULL);

        /* read the result from the shared memory segment */
        s = shm;
        int result = *s;

        /* output the result to the console */
        printf("Result: %d\n", result);

        /* detach and remove the shared memory segment */
        if (shmdt(shm) == -1) {
            perror("shmdt");
            exit(1);
        }
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(1);
        }
    }

    return 0;
}
