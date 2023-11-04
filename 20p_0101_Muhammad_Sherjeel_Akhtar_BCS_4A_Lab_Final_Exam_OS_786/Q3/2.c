#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
int global =0;

int main(){
    int Total=14;
    printf("Total Processes Created: %d\n",Total);
    int status;
    pid_t pid=fork() ; 
    if ( pid == 0 ){
        // p2
        printf("I am Child process with pid %d and i am not waiting\n", getpid());
        pid_t pid2=fork();
        if(pid2==0){
            exit(0);
        }
        if(pid2>0){
            // p5
            pid_t pid3=fork();
            if(pid3==0){
                // p10
            }
            if(pid3>0){
                // p9
            }
        }
    } 
    else if (pid > 0){
        // p3
        printf("I am Parent process with pid %d and i am waiting\n", getpid());
        printf ( " parent PID = %d , child pid = %d\n", getpid(), pid);
        // pid_t exitedChildId=wait(&status);
        wait(NULL);
        printf("I am Parent process and the child with pid is exited\n");
        pid_t pid4=fork();
        if(pid4==0){
            // p7
        }
        if(pid4>0){
            // p6
        }
    }
    else if ( pid < 0){ // if fork() fails 
        printf (" Error in Fork");
    }
    pid_t pid5=fork();
    if(pid5==0){
        exit(0);
    }
    if(pid5>0){
        // p4
        pid_t pid6=fork();
        if(pid6==0){
            exit(0);
        }
        if(pid6>0){
            // p8
            pid_t pid7=fork();
            if(pid7==0){
                exit(0);
            }
            if(pid7>1){
                // p11
                pid_t pid8=fork();
                if(pid8==0){
                    // p13
                }
                if(pid8>0){
                    // p12
                }
                pid_t pid9=fork();
                if(pid9==0){
                    exit(0);
                }
                if(pid9==1){
                    // p14
                }
            }
        }
    }
    // return 0;

}