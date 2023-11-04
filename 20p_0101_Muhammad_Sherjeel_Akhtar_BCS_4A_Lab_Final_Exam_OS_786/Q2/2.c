#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<fcntl.h> 
#include<stdlib.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(){
    // int file;
    int fd[2];
    pid_t childpid; 
    char msg [] = "Image File Name\n";
    char readbuffer[80];
    int result = pipe(fd);
    printf("Value stored in result variable is:%d\n",result);
    if(result<0){
        printf("Error while creating file");
        exit(1) ;
    }
    childpid = fork();
    if(childpid == -1){
        printf("Error in fork...");
        exit(1);
    }
    if(childpid == 0){ // Child process writing to the pipe
        close(fd[0]);
        printf("Child (P1) writing to the pipe \n"); 
        write(fd[1], msg, sizeof(msg));
        close(fd[0]);
        int file = open("hello.txt",O_WRONLY);
        write(file, msg, sizeof(msg));
        // read(fd[0] , readbuffer, sizeof(readbuffer));
        // printf("2) Received string :%s \n",readbuffer);
        printf("Written to a Pipe \n");
        close(file);
        exit(0);
    } 
    else { // Parent process waiting for child to write on Pipe and then read from Pipe
        // p1
        printf("Reading Input\n");
        close(fd[1]);
        wait(NULL);
        printf("Parent (P2) reading from the pipe \n");
        read(fd[0] , readbuffer, sizeof(readbuffer));
        close(fd[0]);
        printf("Received string :%s \n",readbuffer);
        pid_t childpid1=fork();
        if(childpid1==0){
            // p3 Preprocessing
            printf("Parent (P3) appending to file:\n");
            printf("First performing reading     \n");
            read(fd[0],readbuffer,sizeof(readbuffer));
            printf("Read For Preprocess by (P3): %s", readbuffer);
            printf("Closing the reading pipe \n");
            close(fd[0]);
            char append[]="Image File Name Resized";
            write(fd[1],append,sizeof(append));
            int file = open("hello.txt",O_WRONLY);
            write(file, append, sizeof(append));
            close(fd[1]);
            close(file);
            // printf
        }
        if(childpid1>0){
            wait(NULL);
            read(fd[0],readbuffer,sizeof(readbuffer));
            printf("Preprocess data is %s Resized\n ", readbuffer);
            int file = open("hello.txt",O_RDONLY);
            read(file,readbuffer,sizeof(readbuffer));
            printf("From process(P3): %s", readbuffer);
            pid_t childpid2=fork();
            if(childpid2==0){
                int file = open("hello.txt",O_WRONLY);
                char append[]="Analyzed";
                write(fd[1], append , sizeof(append));
                write(file, append, sizeof(append));
                exit(0);
            }
            if(childpid2>0){
                wait(NULL);
                int file = open("hello.txt",O_RDONLY);
                read(file,readbuffer,sizeof(readbuffer));
                printf("\n%s:",readbuffer);
                exit(0);
                // read
            }
        }
        exit(0);
    }
    return 0;
}