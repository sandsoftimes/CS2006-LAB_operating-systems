#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#define ARR_LEN 1000
int main() {
    int arr[ARR_LEN];
    int sum = 0;
    srand(time(NULL));
    for (int i = 0; i < ARR_LEN; i++) {
        arr[i] = rand() % 100;
    }
    int pid1 = fork();
    if (pid1 < 0) {
        printf("error\n");
        exit(1);
    } else if (pid1 == 0) {
        int csum = 0;
        for (int i = 0; i < ARR_LEN/3 + ARR_LEN%3; i++) {
            csum += arr[i];
        }
        exit(csum);
    } else {
        int pid2 = fork();  
        if (pid2 < 0) {
            printf("error\n");
            exit(1);
        } else if (pid2 == 0) {
            int csum = 0;
            for (int i = (ARR_LEN*2)/3; i < ARR_LEN; i++) {
                csum += arr[i];
            }
            exit(csum);
        } else {
            for (int i = ARR_LEN / 3 + ARR_LEN%3; i < (ARR_LEN * 2) / 3; i++) {
                sum += arr[i];
            }
            printf("StartSUm:%d",sum);
            // int status;
            // waitpid(pid1, &status, 0);
            // sum += WEXITSTATUS(status);
            // waitpid(pid2, &status, 0);
            // sum += WEXITSTATUS(status);
            // printf("ArraySum: %d\n", sum);
        }
    }
    return 0;
}