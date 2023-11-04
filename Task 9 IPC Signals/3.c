#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void handle_signal(int sig) {
    printf("Child %d received signal %d\n", getpid(), sig);
}

int main() {
    pid_t child1, child2;

    child1 = fork(); // create first child process

    if (child1 < 0) { // fork() failed
        perror("fork() error");
        exit(1);
    }
    else if (child1 == 0) { // first child process code
        sleep(1); // wait a bit to let second child start
        printf("Child 1 sending signal to Child 2\n");
        kill(getpid() + 1, SIGUSR1); // send SIGUSR1 signal to second child
        exit(0);
    }

    child2 = fork(); // create second child process

    if (child2 < 0) { // fork() failed
        perror("fork() error");
        exit(1);
    }
    else if (child2 == 0) { // second child process code
        signal(SIGUSR1, handle_signal); // register signal handler
        printf("Child 2 waiting for signal\n");
        while (1) { // wait for signal indefinitely
            sleep(1);
        }
        exit(0);
    }

    // parent process code
    wait(NULL); // wait for first child to finish
    wait(NULL); // wait for second child to finish
    printf("Parent process exiting\n");

    return 0;
}
