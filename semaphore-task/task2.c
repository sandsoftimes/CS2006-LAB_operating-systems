#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t sem; 
int value = 10;
void *my_fun ( void *arg ){
    int i = 1 , x;
    sem_wait(&sem);
     sem_getvalue(&sem , &x) ;
    value = value - 5;
    sleep(1);
    value = value + 10;
    printf("\n Adding 10 liter water and removing 5 liter: %d liter ",value);
    pthread_exit(0);
}

int main(){
    int x, i;
    pthread_t tid [5];
    sem_init(&sem , 0 , 3 );
    printf("Statring threads...\n");
    for (i =0; i <5; i ++){ 
        pthread_create(& tid[i] ,NULL,my_fun,NULL);
  
    }
    sleep(2);
    printf ( "\nMain : Going to Post");
    sem_post(&sem ); 
    sem_getvalue(&sem , &x);
    sleep(5); 

    printf( "\nMain : Going to Post" );
    sem_post(&sem);
    sem_getvalue(&sem , &x );
    pthread_exit(0);
}