#include <signal.h>
#include <stdio.h> 
#include <unistd.h>

int main(){
    //kill(49302,SIGKILL);
    printf("49302 is killed by Signal/n");
    while (1)
    {
        kill(15659,SIGKILL);
        printf("Hello Dears %d\n", getpid);
        sleep(1);
    }
    return 0;
}