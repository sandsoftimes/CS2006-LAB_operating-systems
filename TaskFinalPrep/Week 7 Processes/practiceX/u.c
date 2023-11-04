#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    int status;
    pid_t pid1 = fork();
    if (pid1 < 0) {
        printf("error\n");
        exit(1);
    } else if (pid1 == 0) {
        execl("/bin/cat", "cat", argv[1], (char *) NULL);
        printf("Exec error\n");
        exit(1);
    } else {
        wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            pid_t pid2 = fork();
            if (pid2 < 0) {
                printf("error\n");
                exit(1);
            } else if (pid2 == 0) {
                execl("/bin/cat", "cat", argv[1], (char *) NULL);
                printf("Exec error\n");
                exit(1);
            } else {
                wait(&status);
                if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                    exit(0);
                } else {
                    printf("Child process ended not gracefully\n");
                    exit(1);
                }
            }
        } else {
            printf("Child process ended not gracefully\n");
            exit(1);
        }
    }
    return 0;
}