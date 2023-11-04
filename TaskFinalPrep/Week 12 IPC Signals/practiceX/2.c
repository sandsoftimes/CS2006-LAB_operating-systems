#include <signal.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
    // kill(1611101,SIGKILL);
    // printf("1611101 is killed by Signal/n");
    printf("1611101Duo is killed by Signal\n");
    // while(1)
    // {
    //     kill(49302,SIGKILL);
    //     // kill(49302+1,SIGKILL);
    //     printf("Hello Dears %d\n",getpid());
    //     sleep(1);
    // }
    while (1)
    {
        kill(163810,SIGKILL);                                                                                
        printf("Hello Dears: %d\n",getpid());
        sleep(1);
    }
    return 0;
}