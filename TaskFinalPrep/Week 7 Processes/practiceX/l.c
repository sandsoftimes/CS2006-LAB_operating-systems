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
    int sum1;
    int sum2;
    int sum3;
    int csum;
    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++){
    arr[i] = rand() % 100;
    }
    pid_t childprocess=fork();
    if(childprocess==0){
        printf("Child Process ID: %d and PProcess ID: %d\n",getpid(),getppid());
        int status;
        for(int i=0;i<ARRAY_SIZE/3;i++){
            csum+=arr[i];
        }
        printf("csum: %d\n",csum);
        exit(csum);
    }
    else if(childprocess>0){
        // pid_t waitedexit=wait(&exit);
        // printf("Child Process ID: %d and PProcess ID: %d\n",childprocess,getpid());
        // wait(NULL);
        wait(NULL);
        printf("parent process: ");
        for(int i=ARRAY_SIZE/3;i<ARRAY_SIZE;i++){
            sum2+=arr[i];
        }        
        exit(sum2);
    }
    else{
        printf("Fork call failed");
    }
    int status;
    waitpid(childprocess,&status,0);
    sum1=WEXITSTATUS(status);
    waitpid(childprocess,&status,0);
    sum2=WEXITSTATUS(status);

    printf("Sum1 is %d\n",sum1);
    printf("Sum2 is:%d\n",sum2);
    // printf("Array:%d",arr[999]);
}