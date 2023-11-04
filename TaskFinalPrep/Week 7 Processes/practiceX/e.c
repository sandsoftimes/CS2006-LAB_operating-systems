#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<errno.h> 
#include<stdlib.h>
int test=10;
int main() {
    pid_t childpid = fork();
    if ( childpid ==0){ 
        printf ( " I am a child proce with pid = %d \n" , getpid()); 
        printf("The next statement is execv and ls will run \n");
        char* argv []={"ls", "−l", "/usr",NULL};
        execlp("pwd", argv);
        
        printf("Execv failed\n") ;
    }
    else if (childpid > 0){
        wait(NULL) ;
        printf("\n I am parent process with pid = %d and finished waiting \n", getpid());
    }
    // if(childpid>1)
        // printf("\nHi from Parent\n");
    // if(childpid==0)
        // printf("\nHi from Child\n");
    // wait(NULL);
    // if(childpid==0)
        // printf("\nHi from Child\n");
    // if(childpid==1){
        // printf("\nParent Yeseddd1\n");
    // }
    printf(" This Before Fork!  test=%d\n",test);
    pid_t id = fork();
    
    if(id == 0){
        // wait(NULL);
        test += 10; 
        printf(" This in child Fork!  test=%d\n",getpid());
        printf(" This in ppid Fork!  test=%d\n",getppid());
        
    }
    // else{
    //     while(1){
    //         printf(" This in my id Fork!  test=%d\n",getpid());
    //         test += 5;
    //         printf(" In parent Fork!  test=%d\n",test);
    //     }
    // }
    if(id>0){
        wait(NULL);
        printf("\nSomendroO\n");
    }

    return 0;
}