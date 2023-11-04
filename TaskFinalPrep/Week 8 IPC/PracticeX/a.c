#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(){
    // int n;
    int p; 
    // int fd[2];
    int fd2[2];
    // char buf[1025];
    char buf2[1092];
    // char const* data = "Hello this is written to pipe.";
    char const* data2="How are you";
    // pipe(fd);
    pipe(fd2);
    // write(fd[1], data , strlen(data));
    write(fd2[1],data2,strlen(data2));
    if((p=read(fd2[0],buf2,strlen(data2)))>=0){
        buf2[p]=0;
        printf("Read %d bytes from pipe:",p);
        printf("Message Read From Pipe:%s\n",buf2);
    }
    else{
        perror("read");
        exit(0);
    }
    return 0;
    // if((n=read(fd[0], buf, strlen(data))) >=0){
    //     buf [n] = 0;
    //     printf("Read %d bytes from pipe.\n", n);
    //     printf("Message read from Pipe: %s\n", buf);
    // }
    // else{
    //     perror("read");
    //     exit(0);
    // }
    // return 0;
}

