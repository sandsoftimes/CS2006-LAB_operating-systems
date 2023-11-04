#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
void *func1(void *p){
    // void *status=2;
    void *status="Success";
    pthread_exit((void *)status);
}
void *func2(void *p){
    // void *status=3;
    pthread_exit((void*)2);
}
void *func3(void *p){
    void *status="Failed";
    pthread_exit((void *)status);
}
void *func4(void *p){
    void *status="YeseD";
    pthread_exit((void*)status);
}
void *func5(void *p){
    void* valve=2;
    valve=9*2;
    pthread_exit((void*)valve);
}
int main(){
    pthread_t tid1,tid2,tid3;
    pthread_t tid4;
    pthread_t tid5;
    pthread_create(&tid1,NULL,func1,NULL);
    pthread_create(&tid2,NULL,func2,NULL);
    pthread_create(&tid3,NULL,func3,NULL);
    pthread_create(&tid4,NULL,func4,NULL);
    pthread_create(&tid5,NULL,func5,NULL);
    void *tret1;
    void *tret2;
    void *tret3;
    void *tret4;
    void *tret5;
    pthread_join(tid1,&tret1);
    pthread_join(tid2,&tret2);
    pthread_join(tid3,&tret3);
    pthread_join(tid4,&tret4);
    pthread_join(tid5,&tret5);
    printf("Ending After Threads DONE\n");
    printf("Thread 1 code: %s\n",(char*) tret1);
    printf("Thread 2 code: %ld\n",(int*) tret2);
    printf("Thread 3 code: %s\n",(char*) tret3);
    printf("Thread 3 codN: %d\n",(int *) tret3);
    printf("Thread 3 CoLD: %ld\n",(int *) tret3);
    printf("Thread 4 Code: %s\n",(char *) tret4);
    printf("Thread 4 CodD: %d\n",(int *) tret4);
    printf("Thread 4 coLD: %ld\n",(int *) tret4);
    printf("Thread 5 code: %d",(int *) tret5);
    return 0;
}
