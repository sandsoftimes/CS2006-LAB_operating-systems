#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#define SHMSZ 1024
int main()
{
    key_t key2=12345;
    // key_t key = 12345; // We'll name our shared memory segment "12345"
    // int shmid = shmget(key, SHMSZ, 0777 | IPC_EXCL); // Create the segment.
    int shmid2;
    shmid2=shmget(key2,SHMSZ,0777 | IPC_EXCL);
    // char *shm = shmat(shmid, NULL, 0); // Now we attach the segment to our data space.
    char* shm2;
    shm2=shmat(shmid2,NULL,0);
    printf("Shm:%s",shm2);
    // printf("shm = %s\n", shm);
    shmdt(shm2);
    shmctl(shmid2,IPC_RMID,NULL);
    return 0;

    // shmdt(shm);
    // shmctl(shmid, IPC_RMID, NULL);
    // return 0;
}