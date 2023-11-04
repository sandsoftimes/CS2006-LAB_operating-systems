#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(){
    int n; 
    int fd[2];
    char buf[1025];
    char const* data = "Hello this is written to pipe.";
    pipe(fd);
    write(fd[1], data , strlen(data));
    if((n=read(fd[0], buf, strlen(data))) >=0){
        buf [n] = 0;
        printf("Read %d bytes from pipe.\n", n);
        printf("Message read from Pipe: %s\n", buf);
    }
    else{
        perror("read");
        exit(0);
    }
    return 0;
}