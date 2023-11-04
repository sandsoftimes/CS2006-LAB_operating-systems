#include <stdio.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // added for fork()

#define MAX_BUF 1024

int main()
{
    int fifo_server, fifo_client;
    char choice[MAX_BUF];
    char buf[MAX_BUF];

        printf("Welcome to a simple chat application\n\n");

    // create the server FIFO
    mkfifo("fifo_server", 0666);

    // create the client FIFO
    mkfifo("fifo_client", 0666);
    if (fork() == 0) {   
        // child process (read from client FIFO)
        while(1) {
            fifo_client = open("fifo_client", O_RDONLY);
            if (fifo_client < 0) {
                perror("Error opening client FIFO");
                exit(EXIT_FAILURE);
            }

            read(fifo_client, buf, MAX_BUF);
            printf("User1: %s\n", buf);

            close(fifo_client);
        }
    }
    else {
        // parent process (write to server FIFO)
        while(1) {
            printf("Enter message: ");
            scanf("%s", choice);

            fifo_server = open("fifo_server", O_WRONLY);
            if (fifo_server < 0) {
                perror("Error opening server FIFO");
                exit(EXIT_FAILURE);
            }

            write(fifo_server, choice, strlen(choice) + 1);

            close(fifo_server);
        }
    }

    return 0;
}