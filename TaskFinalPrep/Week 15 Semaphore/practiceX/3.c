#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
// Using semaphore as a condtion variable for  IPC/Syncronization
// sem_t sem;
sem_t sem2;
// void *f1 ( void *arg){
    // printf ( " Child: begin\n" ) ;
    // sem_post(&sem);
    // printf("Child : end\n"); 
    // pthread_exit(NULL);
// }
void* func(void* p){
    printf("child: begin\n");
    sem_post(&sem2);
    printf("Child: end\n");
    pthread_exit(NULL);
}
int main(){ 
    // pthread_t tid;
    pthread_t tid2;
    // sem_init(&sem , 0 , 0 ) ;
    sem_init(&sem2,0,0); 
    // printf(" parent : begin\n" );
    printf("parent: begin\n");
    // pthread_create(&tid,NULL, f1 ,NULL);
    pthread_create(&tid2,NULL,func,NULL);
    // sem_wait(&sem);
    sem_wait(&sem2);
    // printf(" parent : end\n" );
    printf("parent: end\n"); 
    // pthread_exit(NULL);
    pthread_exit(NULL);
    return 0;
}