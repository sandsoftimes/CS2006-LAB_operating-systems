#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

#define SHMSZ 1024

int main(){
    key_t k = 12345;
    int x = fork();
    if(x > 0)
    {
        printf("Hello from parent...\n");
        int shmid;
        int *arr;
       
        shmid = shmget(k, sizeof(int)*5, 0777 | IPC_CREAT);
        if (shmid < 0 ){
            perror("shmget");
            exit(1);
        }
        arr = (int *)shmat(shmid, NULL, 0);
        if (arr == (int *) -1){
            perror("shmat");
            exit(1);
        }
        srand(time(NULL));
        int i;
        for(i=0; i<5; i++)
            arr[i] = rand() % 50 + 1;

        sleep(1); // Add a delay to allow child to attach to shared memory segment
       
        int child_sum;
        wait(&child_sum);
        child_sum = WEXITSTATUS(child_sum);
        printf("Sum of array in parent process: %d\n", child_sum);

        shmdt((void *) arr);
        shmctl(shmid, IPC_RMID, NULL);
    }
    else if (x == 0)
    {
        printf("Hello from child...\n");
        int shmid ;
        int *arr;
       
        sleep(1); // Add a delay to allow parent to create shared memory segment

        shmid = shmget(k, sizeof(int)*5, 0777);
        if (shmid < 0 ){
            perror("shmget");
            exit(1);
        }
       
        arr = (int *)shmat(shmid, NULL, 0);
        if (arr == (int *) -1){
            perror("shmat");
            exit(1);
        }
       
        int i, sum = 0;
       printf("Numbers in array: ");
    for(int i=0; i<5; i++)
        printf("%d ", arr[i]);
    printf("\n");
       
        for(i=0; i<5; i++)
            sum += arr[i];

        shmdt((void *) arr);

        exit(sum);
    }

    return 0;
}
    