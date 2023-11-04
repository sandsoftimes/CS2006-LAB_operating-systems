#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handle_signal(int sig) {
    printf("Received signal %d\n", sig);
}

int main() {
    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(1);
    } else if (pid1 == 0) {
        // First child process
        printf("First child process with pid=%d\n", getpid());

        // Send SIGUSR1 signal to second child process
        pid2 = getppid();
        printf("Sending SIGUSR1 signal to process %d\n", pid2);
        kill(pid2, SIGUSR1);

        exit(0);
    }

    // Parent process
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(1);
    } else if (pid2 == 0) {
        // Second child process
        printf("Second child process with pid=%d\n", getpid());

        // Set up signal handler for SIGUSR1
        signal(SIGUSR1, handle_signal);

        // Wait for signal to arrive
        pause();

        exit(0);
    }

    // Parent process
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
