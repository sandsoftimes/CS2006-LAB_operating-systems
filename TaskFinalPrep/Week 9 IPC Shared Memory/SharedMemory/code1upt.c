#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include <sys/wait.h>

#define SHMSZ 1024

int main(){
    key_t k = 12345; // We'll name our shared memory segment "12345"
    int x = fork();
    if(x > 0) ///////// Parent Process
    { 
        //parent - Server Side - write
        printf("Hello from parent...\n");
        int shmid; // shared memory id
        char *shm; // char pointer that points to the shm

        // creating shared memory and checking for error
        shmid = shmget(k, 1024, 0777 | IPC_CREAT);
        if (shmid < 0 ){
            perror("shmget");
            exit(1);
        }

        // attaching data to the shared mem and checking for error
        shm = shmat(shmid, NULL, 0);
        if (shm == (char *) -1){
            perror("shmat");
            exit(1);
        }

        memcpy(shm,"Hello world", 11); // message to be shared
        wait(NULL); // wait for child process to finish
    } // end if x > 0
    else if (x==0) ///////// Child Process
    {
        //child - client side - read
        filenameprintf("Hello from child...\n");
        int shmid ; // shared memory id
        char *shm; // char pointer that points to the shm

        // creating shared memory and checking for error
        shmid = shmget(k, 1024, 0777 | IPC_EXCL);
        if (shmid < 0 ){
            perror("shmget");
            exit(1);
        }

        // attaching data to the shm and checking for error
        shm = shmat(shmid, NULL, 0);
        if (shm == (char *) -1){
            perror("shmat");
            exit(1);
        }

        printf("shm = %s \n",shm);

        // to de-attach data from the shared mem
        shmdt(shm);

        // destroying shared memory
        shmctl(shmid, IPC_RMID, NULL);
    } // end else if

    return 0;
}
