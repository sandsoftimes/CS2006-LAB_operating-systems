#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_SIZE 1024

struct message {
    long message_type;
    char message_text[MAX_SIZE];
};

int main() {
    key_t key;
    int message_id;
    struct message message_buffer;


    key = ftok("message_queue_key", 'A');


    message_id = msgget(key, 0666 | IPC_CREAT);

    if (message_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }


    message_buffer.message_type = 1;
    strcpy(message_buffer.message_text, "Hello from server 1!");
    msgsnd(message_id, &message_buffer, sizeof(message_buffer), 0);

    
    msgrcv(message_id, &message_buffer, sizeof(message_buffer), 1, 0);
    printf("Received message: %s\n", message_buffer.message_text);


    msgctl(message_id, IPC_RMID, NULL);

    return 0;
}