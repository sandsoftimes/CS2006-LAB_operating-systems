#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_signal(int signum) {
    printf("Received signal %d\n", signum);
}

int main() {
    pid_t pid1, pid2;
    int status1, status2;

    // Create first child
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // First child process
        printf("First child process (PID=%d) sending SIGUSR1 to second child process...\n", getpid());
        sleep(1);
        kill(pid2, SIGUSR1);
        exit(EXIT_SUCCESS);
    }

    // Create second child
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        // Second child process
        signal(SIGUSR1, handle_signal);
        printf("Second child process (PID=%d) waiting for signal...\n", getpid());
        while (1) {
            sleep(1);
        }
        exit(EXIT_SUCCESS);
    }

    // Wait for both children to exit
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);

    return 0;
}