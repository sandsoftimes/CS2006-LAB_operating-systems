    // COMMUNICATION BETWEEN DIFFERENT ANCESTRY PROCESSES
#include<unistd.h>
#include<string.h>
#include<fcntl.h> 
#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(){
    char str2[256]="Hello World";
    char str3[256]="";
    // char str[256] = "hello world";
    // int fifo_write ;
    int f1=mkfifo("pipe_one",0666);
    if(f1<0)
        printf("Pipe Not Created\n");
    else{
        printf("pipe one is created\n");
    }
    int fifo_write;
    pid_t childpid=fork();
    if(childpid<-1)
        printf("Failed");
    if(childpid==0);
    // fifo_write=open("pipe_one",O_WRONLY);
    // write
    return 0;
}