#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
void *kidfunc(void *p){
    printf("Kid ID is --->%d\n",getpid());
}
int main(){
    // printf("Parent ID is ----> %d\n",getpid());
    // printf("ParentX ID is ----> %d\n",4);
    pthread_t kid;
    pthread_create(&kid,NULL,kidfunc,NULL);
    printf("Parent ID is --->%d\n",getpid());
    pthread_join(kid,NULL);
    printf("No more KID.");
    return 0;
}