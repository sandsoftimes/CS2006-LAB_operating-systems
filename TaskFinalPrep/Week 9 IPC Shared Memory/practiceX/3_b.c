#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include <stdlib.h>
#define SHMSZ 27
#define SHMSZ2 27
int main(){
    // char c;
    char c2;
    // int shmid;
    int shmid2;
    // key_t key;
    key_t key2;
    // char *shm, *s;
    char *s2;
    char *shm2;
    // key = 5678; // We'll name our shared memory segment "5678"
    key2=5678;
    // if((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        // perror("shmget");
        // exit(1);
    // }
    if((shmid2=shmget(key2,SHMSZ2, IPC_CREAT | 0666))<0){
        perror("Shmget");
        exit(1);
    }
    if((shm2=shmat(shmid2,NULL,0))==(char*)-1){
        perror("shmat");
        exit(1);
    }
    // if((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        // perror("shmat");
        // exit(1);
    // }
    // Now put some things into the memory for the other process to read.
    // s = shm;
    s2=shm2;
    for(c2='a';c2<='z';c2++){
        *s2++=c2;
    }
    // for (c = 'a'; c <= 'z'; c++){
        // *s++ = c;
    // }
    // *s = (char) NULL;
    *s2=(char) NULL;
    /*
     * Finally, we wait until the other process 
     * changes the first character of our memory
     * to '*', indicating that it has read what 
     * we put there.
     */
    while(*shm2!='*'){
        sleep(1);
    }
    // while (*shm != '*'){
        // sleep(1);
    // }
    exit(0);
    return 0;
}