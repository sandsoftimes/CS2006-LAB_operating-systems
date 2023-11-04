#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<errno.h> 
#include<stdlib.h>
int main() {
    // pid_t childpid = fork();
    // pid_t cchildpid=fork();
    pid_t cpchild=fork();
    // if ( childpid ==0){ 
    //     printf ( " I am a child proce with pid = %d \n" , getpid()); 
    //     printf("The next statement is execl and ls will run \n");
    //     execl("/bin/ls", "ls", "/home/zawster" ,NULL) ; 
    //     printf ( " Execl failed " ) ;
    // }
    // if(cchildpid==0){
    //     printf("I'm a child process with pid: %d\n",getpid());
    //     printf("The next statement is execl and ls will run\n");
    //     execlp("ls","ls","/home/spoofy",NULL);
    //     printf("Execl Failed");
    // }
    if(cpchild==0){
        printf("\nChild Process With PID: %d",getpid());
        printf("The next statement to be executed is: ls and -lh");
        execl("/bin/ls","ls","/home/spoofy",NULL);
    }
    // else if (childpid >0){
    //     wait(NULL) ;
    //     printf("\n I am parent process with pid = %d and finished waiting \n", getpid());
    // }
    // else if(cchildpid>0){
    //     wait(NULL);
    //     printf("\nI am a parent process with pid=%d and finished waiting",getpid());
    // }
    else if(cpchild>0){
        wait(NULL);
        printf("\nI'm Parenty And I'm Now Ending. My pid is %d: ",getppid());
    }
    return 0;
}