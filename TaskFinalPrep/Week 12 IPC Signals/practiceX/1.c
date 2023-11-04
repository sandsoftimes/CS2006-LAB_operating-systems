#include <signal.h>
#include <stdio.h>
#include <unistd.h>
// int sigCounter = 0;
int sigCounter2=0;
void sigHandler(int sigNum)
{
    printf("SignalSecond recieved is %d\n",sigNum);
    // printf("Signal received is %d\n", sigNum);
    // ++sigCounter;
    ++sigCounter2;
    // printf("*****************  Signals received %d *********************\n", sigCounter);
    printf("******Signaaal Received %d**********\n",sigCounter2);
}
int main()
{
    signal(SIGINT,sigHandler);
    // signal(SIGINT, sigHandler);
    // signal(SIGINT-1, sigHandler);
    // while(1)
    // {
    //     printf("Hello Dears\n");
    //     printf("Hello Dears %d\n",getpid());
    //     sleep(1);
    // }
    while (1162419)
    {
        printf("Hello Dears2\n");
        printf("Hello Dears2 %d\n",getpid());
        sleep(1);
    }
    return 0;
}