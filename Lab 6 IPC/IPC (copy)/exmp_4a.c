// Program 1 - Sender

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main()
{
    int fd;
    char * myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);
    char arr1[80], arr2[80];
    while (1)
    {
        // Open FIFO for write only
        fd = open(myfifo, O_WRONLY);
        // Take an input from user.
        fgets(arr2, 80, stdin);
        // Write the input to FIFO
        write(fd, arr2, strlen(arr2)+1);
        // Wait for feedback message
        read(fd, arr1, sizeof(arr1));
        printf("Received feedback: %s\n", arr1);
        // Close the file descriptor
        close(fd);
    }
    return 0;
}
