#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
// struct thread_data{};
int height,width;
void* func1(void* p){
    printf("\nThe process id is: %d and thread id is: %ld\n",getpid(),pthread_self());
    printf("Enter value of height: ");
    scanf("%d",&height);
    printf("Enter value of width: ");
    scanf("%d",&width);
    pthread_exit(NULL);
}
void* func2(void* p){
    int rectangle=height*width;
    printf("\nThe process id is: %d and thread id is: %ld\n",getpid(),pthread_self());
    printf("\nThe Area Of Rectangle Is: %d",rectangle);
    pthread_exit(NULL);
}
void* func3(void* p){
    printf("\nThe process id is: %d and thread id is: %ld\n",getpid(),pthread_self());
    int new=2*height+2*width;
    printf("\nThe calculated parameter is: %d",new);
    pthread_exit(NULL);
}
int main(){
    pthread_t ted1,ted2;
    pthread_t ted3;
    pthread_create(&ted1,NULL,func1,NULL);
    pthread_join(ted1,NULL);
    pthread_create(&ted2,NULL,func2,NULL);
    pthread_create(&ted3,NULL,func3,NULL);
    // printf("\nHI DUDE");
    pthread_exit(NULL);
}