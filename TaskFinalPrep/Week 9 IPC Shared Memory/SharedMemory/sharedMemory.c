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
        printf("Heelo from parent...,\n");
        int shmid; // shared memory id
        char *shm; // char pointer that points to the shm
        char *c;
        // creating shared memory and checking for error
        shmid = shmget (k, 1024, 0777 | IPC_CREAT);
        if (shmid < 0 ){
            perror("shmget");
            exit(1);
        } // end if
        // attaching data to the shared mem and checking for error
        shm = shmat(shmid, NULL, 0);
        if (shm == (char *) -1){
            perror("shmat");
            exit(1);
        } // end if
        memcpy(shm,"Hello world", 11); // message to be shared
        wait(NULL);
    } // end if x > 0
    else if (x==0) ///////// Child Process
    {
        //child - client side - read
        printf("hello from Child...\n");
        int shmid ; // shared memory id
        char *shm; // char pointer that points to the shm
        // to creating shared memory and checking for error
        shmid = shmget (k, 1024, 0777 | IPC_EXCL);
        if (shmid < 0 ){
            perror("shmget");
            exit(1);
        } // end if
        // attaching data to the shm and checking for error
        shm = shmat(shmid, NULL, 0);
        if (shm == (char *) -1){
            perror("shmat");
            exit(1);
        } // end if
        // wait(NULL);
        printf("shm = %s \n",shm);
        // to de-attach data from the shared mem
        shmdt(shm);
        // destroying shared memory
        shmctl(shmid, IPC_RMID, NULL);
    } // end else if

    return 0;
}