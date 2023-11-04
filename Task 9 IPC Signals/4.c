#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signum) {
    if (signum == SIGUSR1) {
        printf("Received SIGUSR1 signal.\n");
    }
}

int main() {
    pid_t pid1, pid2;

    // create first child process
    pid1 = fork();
    if (pid1 < 0) {
        fprintf(stderr, "Error: Fork Failed.\n");
        exit(1);
    } else if (pid1 == 0) { // first child process
        // send SIGUSR1 signal to second child process
        pid2 = getppid();
        kill(pid2, SIGUSR1);
        exit(0);
    }

    // create second child process
    pid2 = fork();
    if (pid2 < 0) {
        fprintf(stderr, "Error: Fork Failed.\n");
        exit(1);
    } else if (pid2 == 0) { // second child process
        // handle SIGUSR1 signal
        signal(SIGUSR1, signal_handler);
        while (1) {
            sleep(1); // wait for signal
        }
    }

    // parent process
    // handle SIGUSR1 signal
    signal(SIGUSR1, signal_handler);
    while (1) {
        sleep(1); // wait for signal
    }
    return 0;
}
