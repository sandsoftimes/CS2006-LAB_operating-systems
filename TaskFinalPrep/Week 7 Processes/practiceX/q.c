#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include<errno.h>
// int main() {
//     pid_t childpid = fork();

//     if (childpid == -1) {
//         perror("Fork failed");
//         exit(1);
//     } else if (childpid == 0) {
//         // Child process
//         printf("I am the child process with PID %d\n", getpid());
//         // Perform child process tasks
//         int childResult = 92;
//         exit(childResult);  // Return the result from the child process
//     } else {
//         // Parent process
//         printf("I am the parent process with PID %d\n", getpid());
//         int status;
//         waitpid(childpid, &status, 0);  // Wait for the child process to exit
//         if (WIFEXITED(status)) {
//             int childResult = WEXITSTATUS(status);
//             printf("Child process returned: %d\n", childResult);
//         } else {
//             printf("Child process terminated abnormally\n");
//         }
//     }

//     return 0;
// }

// ------------------------------------------------------------------------------
// int main(){
//     pid_t childprocess=fork();
//     if(childprocess==0){
//         printf("This is a child process with PID: %d\n",getpid());
//         int value=90;
//         exit(value);
//     }
//     else{
//         int status;
//         waitpid(childprocess,&status,0);
//         printf("This is a parent process:%d\n",getpid());
//         int childResult=WEXITSTATUS(status);
//         printf("Value returned is:%d\n",childResult);
//     }
// }

// ------------------------------------------------------------------------------
# define ARRAY_SIZE 1000
int main(){
    int midSum=0;
    int sumL;
    int sumF;
    int arr[ARRAY_SIZE] ;
    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++){
    arr[i] = rand() % 100;
    }
    int childprocess=fork();
    if(childprocess==0){
        printf("This is a child1 process with PID: %d\n",getpid());
        int value;
        for(int i=0;i<ARRAY_SIZE/3;i++){
            value+=arr[i];
        }
        exit(value);
    }
    else{
        // wait(NULL);
        int childprocess2=fork();
        if(childprocess2==0){
            printf("Child2 Process");
            int valid;
            for(int i=ARRAY_SIZE/3;i<ARRAY_SIZE;i++){
                valid+=arr[i];
            }
            exit(valid);
        }
        else{
            // wait(NULL);
            printf("\nParent Process:\n");
            wait(NULL);
            for(int i=0;i<ARRAY_SIZE/2;i++){
                midSum+=arr[i];
            }
            int status;
            waitpid(childprocess,&status,0);
            sumF=WEXITSTATUS(status);
            waitpid(childprocess2,&status,0);
            sumL=WEXITSTATUS(status);
            printf("Sum form F:%d\n",sumF);
            printf("Sum form L:%d\n",sumL);
            printf("Sum from Parent:%d\n",midSum);
        }
        

        // printf("This is a parent process:%d\n",getpid());
        // int status;
        // waitpid(childprocess,&status,0);
        // int childResult=WEXITSTATUS(status);
        // printf("Value returned is:%d\n",childResult);
    }
}
