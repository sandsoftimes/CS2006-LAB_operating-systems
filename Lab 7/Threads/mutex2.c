#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int myGlobal = 0;
pthread_mutex_t myMutex;
void *threadFunction()
{
    int i, j;
    for (i = 0; i<5; i++)
    {
        pthread_mutex_lock(&myMutex);
        j = myGlobal;
        j = j+1;
        sleep(1);
        myGlobal = j;
        pthread_mutex_unlock(&myMutex);
        printf("\n Child My Global Is: %d\n", myGlobal);
    }
}
int main(){
    pthread_t myThread;
    int i,k;
    pthread_create(&myThread, NULL,
    threadFunction,NULL);
    for (i = 0; i < 5; i++){
        pthread_mutex_lock(&myMutex);
        k = myGlobal;
        k = k+1;
        sleep(1);
        myGlobal = k;
        pthread_mutex_unlock(&myMutex);
        printf("\n Parent My Global Is: %d\n", myGlobal);
    }
    pthread_join(myThread, NULL);
    printf("\nMy Global Is: %d\n", myGlobal);
    exit(0);
}