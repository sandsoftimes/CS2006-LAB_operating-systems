#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUF 1024

int main()
{
    int fifo_server, fifo_client;
    char buf[MAX_BUF];
    char choice[MAX_BUF];

    printf("Welcome to a simple chat application\n\n");

    if (fork() == 0) {
        // Child process (write to server FIFO)
        while (1) {
            printf("Enter message: ");
            fflush(stdout); // flush stdout before reading input

            if (fgets(buf, MAX_BUF, stdin) != NULL) {
                // remove trailing newline from input
                buf[strcspn(buf, "\n")] = 0;

                // Open server FIFO for writing
                fifo_server = open("fifo_server", O_WRONLY);
                if (fifo_server < 0) {
                    perror("Error opening server FIFO");
                    exit(EXIT_FAILURE);
                }

                // Write message to server FIFO
                if (write(fifo_server, buf, strlen(buf) + 1) < 0) {
                    perror("Error writing to server FIFO");
                    exit(EXIT_FAILURE);
                }

                // Close server FIFO
                close(fifo_server);
            }
        }
    } else {
        // Parent process (read from client FIFO)
        while (1) {
            // Open client FIFO for reading
            fifo_client = open("fifo_client", O_RDONLY);
            if (fifo_client < 0) {
                perror("Error opening client FIFO");
                exit(EXIT_FAILURE);
            }

            // Read message from client FIFO
            if (read(fifo_client, choice, MAX_BUF) < 0) {
                perror("Error reading from client FIFO");
                exit(EXIT_FAILURE);
            }

            // Print message from client FIFO
            printf("User1: %s\n", choice);

            // Close client FIFO
            close(fifo_client);
        }
    }

    return 0;
}