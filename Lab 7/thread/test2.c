#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
void *kidfunc(void *p){
    printf("Kid ID is ----> %d\n",getpid());
    while(1){
        printf("Hi");
    }
}
int main(){
    pthread_t kid;
    pthread_create(&kid,NULL,kidfunc,NULL);
    printf("Hello\n",getpid());
    //pthread_join(kid,NULL);
    printf("No more kid!\n");
    return 0;
}