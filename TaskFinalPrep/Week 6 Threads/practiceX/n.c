#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
// int myGlobal = 0;
int myGlobal2=0;

// void *threadFunction()
// {
//     int i, j;
//     for (i = 0; i<5; i++){
//         j = myGlobal;
//         j = j+1;
//         sleep(1);
//         myGlobal = j;
//         printf("\n Child My Global Is: %d\n", myGlobal);
//     }
// }
void* func(void* p){
    int i,j;
    for(int i=0;i<5;i++){
        j=myGlobal2;
        j=j+1;
        sleep(1);
        myGlobal2=j;
        printf("\nChildM My Global Is: %d",myGlobal2);
    }
    pthread_exit(NULL);
}
int main(){
    // pthread_t myThread;
    pthread_t myThread2;
    // int i,k;
    int m,n;
    // pthread_create(&myThread, NULL, threadFunction,NULL);
    pthread_create(&myThread2,NULL,func,NULL);
    // for (i = 0; i < 5; i++)sem_post(&sem);
    // {
    //     k = myGlobal;
    //     k = k+1;
    //     sleep(1);
    //     myGlobal = k;
    //     printf("\n Parent My Global Is: %d\n", myGlobal);
    // }
    for(m=0;m<5;m++){
        n=myGlobal2;
        n=n+1;
        sleep(1);
        myGlobal2=n;
        printf("\n ParentM My Global Is: %d\n",myGlobal2);
    }
    // pthread_join(myThread, NULL);
    pthread_join(myThread2,NULL);
    // printf("\nMy Global Is: %d\n", myGlobal);
    printf("\nMy GlobalM Is: %d\n",myGlobal2);
    exit(0);
}