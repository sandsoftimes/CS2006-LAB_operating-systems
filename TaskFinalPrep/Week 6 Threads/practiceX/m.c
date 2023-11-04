#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
void* func(void* p){
    int* status=p;
    while(++(*status)<100);
    printf("HI Doing!");
    // pthread_exit((void*) status);
    int jako=*status;
    pthread_exit((void*) jako);
}
void* main(){
    pthread_t thread;
    int x=0;
    int rc;
    rc=pthread_create(&thread,NULL,func,&x);
    if(rc){
        printf("Error Observed.");
        exit(-1);
    }
    void* ted;
    // pthread_join(thread,&ted);
    printf("Everything Done");
    printf("Si %ld",(long*)ted);
    pthread_exit(NULL);
}