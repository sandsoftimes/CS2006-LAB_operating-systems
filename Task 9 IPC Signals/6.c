#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_signal(int sig)
{
    printf("Child process %d received signal %d\n", getpid(), sig);
}

int main()
{
    pid_t pid1, pid2;

    // create first child process
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(1);
    } else if (pid1 == 0) {
        // first child process
        sleep(1); // wait for second child process to initialize signal handler
        kill(getppid(), SIGUSR1); // send SIGUSR1 signal to parent process
        exit(0);
    }

    // create second child process
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(1);
    } else if (pid2 == 0) {
        // second child process
        signal(SIGUSR1, handle_signal); // handle SIGUSR1 signal
        while (1); // wait for signal
    }

    // parent process
    signal(SIGUSR1, handle_signal); // handle SIGUSR1 signal
    pause(); // wait for signal from first child process
    kill(pid2, SIGUSR1); // send SIGUSR1 signal to second child process
    pause(); // wait for signal from second child process

    return 0;
}
