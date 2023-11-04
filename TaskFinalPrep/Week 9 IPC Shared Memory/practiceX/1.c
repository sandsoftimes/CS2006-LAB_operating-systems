#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include <sys/wait.h>

// #define SHMSZ 1024
#define SHMSZ2 1024
int main(){
    // key_t k = 12345; // We'll name our shared memory segment "12345"
    key_t k2=22328;
    // int x = fork();
    int y=fork();
    // if(x > 0) ///////// Parent Process
    // { 
    //     //parent - Server Side - write
    //     printf("Hello from parent...\n");
    //     int shmid; // shared memory id
    //     char *shm; // char pointer that points to the shm

    //     // creating shared memory and checking for error
    //     shmid = shmget(k, 1024, 0777 | IPC_CREAT);
    //     if (shmid < 0 ){
    //         perror("shmget");
    //         exit(1);
    //     }

    //     // attaching data to the shared mem and checking for error
    //     shm = shmat(shmid, NULL, 0);
    //     if (shm == (char *) -1){
    //         perror("shmat");
    //         exit(1);
    //     }

    //     memcpy(shm,"Hello world", 11); // message to be shared
    //     wait(NULL); // wait for child process to finish
    // } // end if x > 0
    if(y>0){
        printf("Hello from parent: \n");
        int shmid;
        char* shm;
        shmid=shmget(k2,1024,0777 | IPC_CREAT);
        if(shmid<0){
            perror("shmget");
            exit(1);
        }
        shm=shmat(shmid,NULL,0);
        if(shm==(char *)-1){
            perror("shmat");
            exit(1);
        }
        memcpy(shm,"YO what is up",15);
        wait(NULL);
    }
    else if(y==0){
        printf("Hello from Child Process \n: ");
        int shmid;
        char* shm;
        shmid=shmget(k2,1024,0777 | IPC_EXCL);
        if(shmid<0){
            perror("Shmid");
            exit(1);
        }
        shm=shmat(shmid,NULL,0);
        if(shm==(char* )-1){
            perror("shm");
            exit(1);
        }
        printf("Shm=%s\n",shm);
        shmdt(shm);
        shmctl(shmid,IPC_RMID,NULL);
        }
        return 0;
    // else if (x==0) ///////// Child Process
    // {
    //     //child - client side - read
    //     printf("Hello from child...\n");
    //     int shmid ; // shared memory id
    //     char *shm; // char pointer that points to the shm

    //     // creating shared memory and checking for error
    //     shmid = shmget(k, 1024, 0777 | IPC_EXCL);
    //     if (shmid < 0 ){
    //         perror("shmget");
    //         exit(1);
    //     }

    //     // attaching data to the shm and checking for error
    //     shm = shmat(shmid, NULL, 0);
    //     if (shm == (char *) -1){
    //         perror("shmat");
    //         exit(1);
    //     }

    //     printf("shm = %s \n",shm);

    //     // to de-attach data from the shared mem
    //     shmdt(shm);

    //     // destroying shared memory
    //     shmctl(shmid, IPC_RMID, NULL);
    // } // end else if

    // return 0;
}
