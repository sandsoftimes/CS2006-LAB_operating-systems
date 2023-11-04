#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *PrintHello(void *threadid)
{
    printf("\n%d: Hello World!\n", threadid);
    pthread_exit(NULL);
}
void* func(void* p){
    printf("Hello World from %d\n",p);
    pthread_exit(NULL);
}
int main()
{
    pthread_t threads[3];
    pthread_t thready[4];
    int kc;int z;
    int rc; int t;
    for(t=0; t<3; t++)
    {
        printf("In main: creating thread\n", t);
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
        if(rc){ // other than 0 return value
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
        pthread_join(threads[t], NULL );
    }
    for(int z=0;z<4;z++){
        printf("Im mainM: creating thread\n",z);
        // printf("Im mainM: creating thread: %d\n",z);
        kc=pthread_create(&thready[z],NULL,func,(void*) z);
        if(kc){
            printf("Error Error from pthread_create\n");
            exit(-1);
        }
        pthread_join(thready[z],NULL);
    }
    // pthread_join(thready[3],NULL);
    printf("Exiting main\n");
    pthread_exit(NULL);
    // pthread_exit(NULL);
}