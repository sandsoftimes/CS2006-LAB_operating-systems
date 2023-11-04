#include <signal.h>
#include <stdio.h> 
#include <unistd.h>
int sigCounter=0;
void sigHandler(int sigNum){
    printf("Signal recieved is %d\n",sigNum);
    ++sigCounter;
   printf("**************************************\n",sigCounter);
}
int main(){
    signal(SIGINT,sigHandler);
    while(1){
        printf("Hello Dears\n");
        printf("Hello Dears %d\n", getpid());   
        sleep(1);
    }
    return 0;
}