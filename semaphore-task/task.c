#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t sem; 
int value = 10;
void *my_fun ( void *arg ){ 
    sem_wait(&sem);
    value = value - 5;
    
    sleep(1);
    value = value + 10;
    sem_post(&sem);
   
    printf("\n Adding 10 liter water and removing 5 liter: %d liter ",value);
    
    
    pthread_exit (NULL) ;
}

int main(){
    pthread_t tid [5];
    sem_init(&sem , 0 , 1 );
    printf("Statring threads...\n");
    for (int i =0; i <5; i ++){ 
        pthread_create(& tid[i] ,NULL ,my_fun,NULL);
  
    }

  
    pthread_exit (NULL);
}