#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int myGlobal = 0;

void *threadFunction()
{
    int i, j;
    for (i = 0; i<5; i++){
        j = myGlobal;
        j = j+1;
        sleep(1);
        myGlobal = j;
        printf("\n Child My Global Is: %d\n", myGlobal);
    }
}
int main(){
    pthread_t myThread;
    int i,k;
    pthread_create(&myThread, NULL, threadFunction,NULL);
    for (i = 0; i < 5; i++)
    {
        k = myGlobal;
        k = k+1;
        sleep(1);
        myGlobal = k;
        printf("\n Parent My Global Is: %d\n", myGlobal);
    }
    pthread_join(myThread, NULL);
    printf("\nMy Global Is: %d\n", myGlobal);
    exit(0);
}