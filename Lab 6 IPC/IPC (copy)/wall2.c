// Program 2 - Receiver

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
        // Open FIFO for read only
        fd = open(myfifo, O_RDONLY);
        // Wait for a message to be received
        read(fd, arr1, sizeof(arr1));
        // Print the message received
        printf("Received message: %s\n", arr1);
        // Send feedback message
        printf("Enter feedback message: ");
        fgets(arr2, 80, stdin);
        // Write the feedback message to FIFO
        write(fd, arr2, strlen(arr2)+1);
        // Close the file descriptor
        close(fd);
    }
    return 0;
}
