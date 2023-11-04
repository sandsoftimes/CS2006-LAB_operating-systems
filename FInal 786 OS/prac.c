#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void sigHandle(int sig)
{
    printf("Child process %d received signal %d\n", getpid(), sig);
}
int main()
{
    pid_t pid1, pid2;
    int status1, status2;
    pid1 = fork();
    if (pid1 == 0) 
    {
        pid2 = getppid();
        signal(SIGUSR1, sigHandle);
        printf("First child process %d waiting for signal\n", getpid());
        while (1) {} 
        return 0;
    }

    pid2 = fork();
    if (pid2 == 0) 
    {
        sleep(1); 
        printf("Sending signal from second child process %d to first child process %d\n", getpid(), pid1);
        kill(pid1, SIGUSR1);
        return 0;
    }
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);
    return 0;
}
