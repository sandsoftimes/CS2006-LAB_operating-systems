#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<pthread.h>
// #include<semaphore.h>
#include<semaphore.h>
#include<unistd.h>
sem_t sem;
int water;
void* func1(void* func){
    int value;
    sem_getvalue(&sem,&value);
    printf("Before Wait Sem in Water Add: %d \n",value);
    sem_wait(&sem);
    water=water+10;
    pthread_exit(0);
}
void* func2(void* p){
    int value;
    // sem_getvalue(&sem,&value);
    // printf("Before Wait Sem in Add: %d \n",value);
    // sem_wait(&sem);
    sem_wait(&sem);
    // sem_wait(&sem);
    water=water-5;
    printf("After Sem:Wait in Water Remove: %d\n",value);
    pthread_exit(0);
}
int main(){
    pthread_t tid1,tid2[5];
    sem_init(&sem,0,0);
    sem_post(&sem);
    pthread_create(&tid1,NULL,func1,NULL);
    pthread_join(tid1,NULL);
    for(int i=5;i<5;i++){
    sem_post(&sem);
    pthread_create(&tid2[i],NULL,func2,NULL);
    pthread_join(tid2[i],NULL);
    }
    printf("Water is: %d\n",water);
    return 0;
}