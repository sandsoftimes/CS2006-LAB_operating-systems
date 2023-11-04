#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
#define ARRAY_SIZE 1000
// Generate random array
int main(){
    int arr[ARRAY_SIZE]={};
    int sum1=0;
    int sum2=0;
    int sum3=0;
    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++){
    arr[i] = rand() % 100;
    }
    pid_t childprocess=fork();
    if(childprocess==0){
        printf("Child Process Child Process ID: %d and PProcess ID: %d\n",getpid(),getppid());
        int status;
        for(int i=0;i<ARRAY_SIZE/3;i++){
            sum1+=arr[i];
        }
        exit(status);
    }
    else if(childprocess>0){
        pid_t waitedexit=wait(&exit);
        printf("Parent Process and Child Process ID: %d and PProcess ID: %d\n",childprocess,getpid());
        // wait(NULL);
        for(int i=ARRAY_SIZE/2;i<ARRAY_SIZE;i++){
            sum2+=arr[i];
        }        
        // exit(status2);
    }
    else{
        printf("Fork call failed");
    }
    pid_t id2=fork();
    if(id2==0){
        printf("Child Process 2\n");
        // pid_t waitedexit=wait(&exit);
        // printf("Parent Process and Child Process ID: %d and PProcess ID: %d\n",childprocess,getpid());
        // wait(NULL);
        // for(int i=ARRAY_SIZE/3;i<ARRAY_SIZE;i++){
            // sum3+=arr[i];
        // }
        for(int i=0;i<ARRAY_SIZE/2;i++){
            sum3+=arr[i];
        }        
        // exit(status2);
    }
    else{
        exit(NULL);
    }
    pid_t id3=fork();
    if(id3<0){
        return -1;
    }
    if(id3==0){
        for(int i=ARRAY_SIZE/4;i<ARRAY_SIZE-50;i++){
            sum1+=arr[i];
        }
    }
    else{
        exit(NULL);
    }
    // wait(NULL);
    printf("Sum1 is %d\n",sum1);
    printf("Sum2 is:%d\n",sum2);
    printf("Sum3 is:%d\n",sum3);
    // printf("Array:%d",arr[999]);
}