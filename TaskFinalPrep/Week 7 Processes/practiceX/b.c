#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/wait.h>
int main(){
    pid_t childpid=fork();
    // printf(childpid);
    if(childpid==0)
    printf("\nChild Process");
    if(childpid>0){
        printf("\nno its parent");
    }
    if(childpid<0){
        printf("Error in forK");
    }
}