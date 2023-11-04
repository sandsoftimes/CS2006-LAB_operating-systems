#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define ARR_LEN 1000

int main() {
    int arr[ARR_LEN];
    int sum = 0;

    // generate random array of integers
    srand(time(NULL));
    for (int i = 0; i < ARR_LEN; i++) {
        arr[i] = rand() % 100;
    }

    // create two child processes
    int pid1 = fork();
    if (pid1 < 0) {
        printf("Fork error\n");
        exit(1);
    } else if (pid1 == 0) {
        // first child process handles first 1/3 of array
        int child_sum = 0;
        for (int i = 0; i < ARR_LEN / 3; i++) {
            child_sum += arr[i];
        }
        exit(child_sum);
    } else {
        int pid2 = fork();
        if (pid2 < 0) {
            printf("Fork error\n");
            exit(1);
        } else if (pid2 == 0) {
            // second child process handles last 1/3 of array
            int child_sum = 0;
            for (int i = (ARR_LEN * 2) / 3; i < ARR_LEN; i++) {
                child_sum += arr[i];
            }
            exit(child_sum);
        } else {
            // parent process handles middle 1/3 of array
            for (int i = ARR_LEN / 3; i < (ARR_LEN * 2) / 3; i++) {
                sum += arr[i];
            }
            // wait for child processes to finish and get their sums
            int status;
            waitpid(pid1, &status, 0);
            sum += WEXITSTATUS(status);
            waitpid(pid2, &status, 0);
            sum += WEXITSTATUS(status);
            // print final sum
            printf("Sum of array: %d\n", sum);
        }
    }

    return 0;
}