#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
  int shm_id;
  int *shm_ptr;
  pid_t pid;
  
  // create a shared memory segment
  if ((shm_id = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
    perror("shmget");
    exit(1);
  }

  // attach the shared memory segment to the parent process
  if ((shm_ptr = shmat(shm_id, NULL, 0)) == (int *) -1) {
    perror("shmat");
    exit(1);
  }

  // write an array of integers to the shared memory segment from the parent process
  int arr[] = {1, 2, 3, 4, 5};
  for (int i = 0; i < 5; i++) {
    shm_ptr[i] = arr[i];
  }

  // create a child process
  if ((pid = fork()) < 0) {
    perror("fork");
    exit(1);
  } else if (pid == 0) { // child process
    // read the array of integers from the shared memory segment
    int arr[5];
    for (int i = 0; i < 5; i++) {
      arr[i] = shm_ptr[i];
    }

    // perform a series of operations on the array
    for (int i = 0; i < 5; i++) {
      arr[i] = arr[i] * 2;
    }

    // write the results back to the shared memory segment
    for (int i = 0; i < 5; i++) {
      shm_ptr[i] = arr[i];
    }

    exit(0);
  } else { // parent process
    // wait for the child process to finish
    wait(NULL);

    // read the results from the shared memory segment
    int results[5];
    for (int i = 0; i < 5; i++) {
      results[i] = shm_ptr[i];
    }

    // output the results to the console
    printf("Results: ");
    for (int i = 0; i < 5; i++) {
      printf("%d ", results[i]);
    }
    printf("\n");

    // detach the shared memory segment from the parent process
    if (shmdt(shm_ptr) == -1) {
      perror("shmdt");
      exit(1);
    }

    // delete the shared memory segment
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
      perror("shmctl");
      exit(1);
    }
  }

  return 0;
}
