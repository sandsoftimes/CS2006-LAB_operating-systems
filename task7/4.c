#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork error\n");
        exit(1);
    } else if (pid == 0) {
        // child process
        if (execl("/bin/cat", "cat", argv[1], (char *) NULL) < 0) {
            fprintf(stderr, "Exec error\n");
            exit(1);
        }
    } else {
        // parent process
        int status;
        wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            // spawn another child process to run cat on the file
            pid_t pid2 = fork();
            if (pid2 < 0) {
                fprintf(stderr, "Fork error\n");
                exit(1);
            } else if (pid2 == 0) {
                if (execl("/bin/cat", "cat", argv[1], (char *) NULL) < 0) {
                    fprintf(stderr, "Exec error\n");
                    exit(1);
                }
            } else {
                // wait for child process to finish and terminate
                wait(&status);
            }
        }
    }

    return 0;
}
