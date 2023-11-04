#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
// sem_t sem;
sem_t sem2;
// void *f1( void *arg){
    // int i =1 , value;
    // sem_wait(&sem );
    // sem_getvalue(&sem , &value ) ;
    // printf("Thread with ID %ld return from wait ( ) and Sem state is :%d\n" , pthread_self() , value);
    // pthread_exit(0);
// }
void* func(void* p){
    int i=1;
    int value;
    sem_getvalue(&sem2,&value);
    printf("Thread with ID %ld return the Sem value:%d\n",pthread_self(),value);
    sem_wait(&sem2);
    
    sem_getvalue(&sem2,&value);
    printf("Thread with ID %ld return from wait() and Sem state is: %d\n", pthread_self(), value);
    pthread_exit(0);
}
int main(){
    pthread_t tid[5];

    // pthread_t tid [5];
    // int value , i ;
    int value;
    int i;
    sem_init(&sem2,0,3);
    // sem_init(&sem , 0 , 3 );
    // for ( i =0; i <5; i ++){ 
        // pthread_create(& tid[i] ,NULL, f1 ,NULL) ;
    // }
    for(i=0;i<5;i++)
        pthread_create(&tid[i],NULL,func,NULL);
    // sleep(5);
    sleep(6);
    printf("main: Going to Post\n");
    // printf ( "Main : Going to Post\n");
    // sem_post(&sem ); 
    sem_post(&sem2);
    // sem_getvalue(&sem , &value );
    sem_getvalue(&sem2,&value);
    printf("Main: After Post sem state:%d\n",value);
    // printf("Main : After Post sem state :%d \n" , value ); 
    // sleep(5); 
    sleep(6);
    // printf( "Main : Going to Post\n" );
    printf("Main: Goinng to post\n");
    // sem_post(&sem);
    sem_post(&sem2);
    // sem_getvalue(&sem , &value );
    sem_getvalue(&sem2,&value);
    printf ( "Main : After Post sem state :%d \n" , value ); 
    pthread_exit(0);
}