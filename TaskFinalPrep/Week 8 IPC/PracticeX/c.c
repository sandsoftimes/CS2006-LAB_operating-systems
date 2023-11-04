#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(){
    // int fd[2];
    int fd2[2];
    pid_t childpid2;
    // pid_t childpid; 
    // char msg [] = "Hello from child\n";
    char msg2[]="Hello From Child";
    // char readbuffer[80];
    char readbuffer2[80];
    // int result = pipe(fd);
    int result2=pipe(fd2);
    printf("Value stored in result variable is:%d\n",result2);
    // if(result<0){
    //     printf("Error while creating file");
    //     exit(1) ;
    // }
    if(result2<0){
        printf("Error while creating file");
        exit(1);
    }
    // childpid = fork();
    childpid2=fork();
    // if(childpid == -1){
    //     printf("Error in fork...");
    //     exit(1);
    // }
    if(childpid2==-1){
        printf("Error in fork");
        exit(1);
    }
    // if(childpid == 0){ // Child process writing to the pipe
    //     close(fd[0]);
    //     printf("Child writing to the pipe \n"); 
    //     write(fd[1], msg, sizeof(msg)); 
    //     // read(fd[0] , readbuffer, sizeof(readbuffer));
    //     // printf("2) Received string :%s \n",readbuffer);
    //     printf("Written to a Pipe \n");
    //     exit(0);
    // }
    if(childpid2==0){
        close(fd2[0]);
        printf("Child is writing to the pipe\n");
        write(fd2[1],msg2,sizeof(msg2));
        printf("Written to a Pipe\n");
        exit(0);
    } 
    // else { // Parent process waiting for child to write on Pipe and then read from Pipe
    //     close(fd[1]);
    //     wait(NULL);
    //     printf("Parent reading from the pipe \n");
    //     read(fd[0] , readbuffer, sizeof(readbuffer));
    //     printf("Received string :%s \n",readbuffer);
    //     exit(0);
    // }
    else{
        close(fd2[1]);
        wait(NULL);
        printf("Parent reading form the pipe\n");
        read(fd2[0],readbuffer2,sizeof(readbuffer2));
        printf("Recieved String:%s\n",readbuffer2);
        exit(0);
    }
    return 0;
}