#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
void *kidfunc(void *p){
    printf("Kid ID is --->%d\n",getpid());
}
void *func(void *p){
    printf("Another Process ID is --->%d\n",getpid());
}
void *func3(void *p){
    printf("A\n");
    printf("A\n");
    printf("A\n");
    for(int i=0;i<3;i++){}
    // printf("Hi: %d\n",4); 
}
int main(){
    // printf("Parent ID is ----> %d\n",getpid());
    // printf("ParentX ID is ----> %d\n",4);
    pthread_t kid;
    pthread_t kid2;
    pthread_t kid3;
    pthread_create(&kid2,NULL,func,NULL);
    pthread_create(&kid,NULL,kidfunc,NULL);
    pthread_create(&kid3,NULL,func3,NULL);
    printf("Parent ID is --->%d\n",getpid());
    pthread_join(kid,NULL);
    pthread_join(kid2,NULL);
    pthread_join(kid3,NULL);
    printf("No more KID.");
    return 0;
}