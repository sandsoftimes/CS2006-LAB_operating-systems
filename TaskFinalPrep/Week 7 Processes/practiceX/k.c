#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 1000

int main() {
    int arr[ARRAY_SIZE] = {};
    int sum1 = 0;
    int sum2 = 0;
    srand(time(NULL));

    // Generate random array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % 100;
    }

    sum2 = 0;  // Initialize sum2

    pid_t childprocess = fork();

    if (childprocess == 0) {
        printf("Child Process ID: %d and Parent Process ID: %d\n", getpid(), getppid());
        for (int i = 0; i < ARRAY_SIZE / 3; i++) {
            sum1 += arr[i];
        }
        exit(0);
    } else if (childprocess > 0) {
        pid_t waitedexit = wait(NULL);
        printf("Child Process ID: %d and Parent Process ID: %d\n", childprocess, getpid());
        for (int i = ARRAY_SIZE / 3; i < ARRAY_SIZE; i++) {
            sum2 += arr[i];
        }
    } else {
        perror("Fork call failed");
        exit(1);
    }

    printf("Sum1 is %d\n", sum1);
    printf("Sum2 is: %d\n", sum2);

    return 0;
}
