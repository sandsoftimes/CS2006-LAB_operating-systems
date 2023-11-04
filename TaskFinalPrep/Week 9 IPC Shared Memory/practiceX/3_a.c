#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include <stdlib.h>
#define SHMSZ 27
int main(){
    // int shmid;
    int shmid2;
    // key_t key;
    key_t key2;
    // char *shm, *s;
    char* shm2;
    char* s;
    /*
     * We need to get the segment named
     * "5678", created by the server.
     */
    // key = 5678;
    key2=5678;
    /*
     * Locate the segment.
     */
    if((shmid2=shmget(key2,SHMSZ,0666 ))<0){
        perror("Error in shmget...\n");
        exit(1);
    }
    // if ((shmid = shmget(key, SHMSZ, 0666)) < 0)
    // {
        // perror("Error in shmget...\n");
        // exit(1);
    // }
    /*
     * Now we attach the segment to our data space.
     */
    if((shm2=shmat(shmid2,NULL,0))==(char*)-1){
        perror("Shmat2: \n");
        exit(1);
    }
    for(s=shm2;*s!=NULL;s++){
        putchar(*s);
        putchar('\n');
    }
    // if((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        // perror("Error in shmat...\n");
        // exit(1);
    // }
    /*
     * Now read what the server put in the memory.
     */
    // for (s = shm; *s != NULL; s++){
        // putchar(*s);
        // putchar('\n');
    // }
    /*
     * Finally, change the first character of the 
     * segment to '*', indicating we have read 
     * the segment.
     */
    *shm2 = '*';
    shmdt(shm2);
    
    shmctl(shmid2,IPC_RMID,NULL);
    exit(0);
    return 0;
}