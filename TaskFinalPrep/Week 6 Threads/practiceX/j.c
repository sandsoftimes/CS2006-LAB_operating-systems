/*
    PASSING A RGUMENTS TO THREADS
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *inc_x( void *arg) { /* increment x to 100 */ 
    printf("Thread : Process Id is %d and Thread Id is %ld\n" , getpid(), pthread_self());
    int *input;
    input =( int *) arg ; 
    while (++(*input) < 100);
    printf ( "x increment finished\n");
    /* the function must return something − NULL will do */ 
    pthread_exit(NULL);
}
void* func(void* p){
    printf("Thread: Process Id is %d and Thread Id is: %ld\n",getpid(),pthread_self());
    int* val=p;
    while(++(*val)<100);
    printf("j incrememnt finished\n");
    pthread_exit(NULL);
}
int main(){
    // main Thread
    int j=0,k=0;
    int x = 0, y = 0;
    printf("x:%d, y:%d are the initial values.\n",x,y);
    printf("x : %d , y : %d\n", x ,y); // show initials values
    printf("main :Process Id is %d and Thread Id is %ld\n", getpid(), pthread_self());
    printf("main: ProcessM Id is %d and ThreadM Id is %ld\n",getpid(),pthread_self());

    //this variable is our reference to the second thread 
    pthread_t thread_2;
    pthread_t thread_3;
    // create a second thread which executes inc_x(&x )
    pthread_create(&thread_2 , NULL, inc_x , &x);
    pthread_create(&thread_3,NULL,func,&j);
    // increment y to 100 in the f i r s t thread 
    while(++y < 100);
    printf("y increment finished\n");
    while(++k<100);
    printf("k increment finished\n");

    /* wait for the second thread to finish */
    pthread_join(thread_2 , NULL);
    pthread_join(thread_3, NULL);
    printf("x : %d , y : %d\n" , x ,y );
    printf("j:%d and k:%d\n",j,k);

    pthread_exit (NULL);
    // pthread_exit(NULL);
}