#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

// sem_t sem;
sem_t sem2;
// void* f1(void* arg){
    // sem_wait(&sem);
    // printf("Thread with ID:%ld got lock\n",pthread_self());
    // sleep(5);
    // sem_post(&sem);
    // pthread_exit(NULL); 
// }
void* func2(void* p){
    sem_wait(&sem2);
    printf("Thread with ID: %ld got lock\n",pthread_self());
    sleep(5);
    sem_post(&sem2);
    pthread_exit("NULL");
}

int main(){
    // pthread_t tid1,tid2;
    pthread_t tid3,tid4;
    sem_init(&sem2,0,1);
    // sem_init(&sem,0,1);
    // printf("Starting Threads....\n");
    printf("Starting Threads2.....\n");
    // pthread_create(&tid1,NULL,f1,NULL);
    pthread_create(&tid3,NULL,func2,NULL);
    // pthread_create(&tid2,NULL,f1,NULL);
    pthread_create(&tid4,NULL,func2,NULL);
    // pthread_exit(NULL);
    pthread_exit(NULL);

}