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

    // Generate a unique key for the message queue
    key = ftok("message_queue_key", 'A');

    // Connect to the message queue
    message_id = msgget(key, 0666);

    if (message_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Send a message to user 1
    message_buffer.message_type = 1;
    strcpy(message_buffer.message_text, "Hello from User 3");

    if (msgsnd(message_id, &message_buffer, sizeof(message_buffer.message_text), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    // Receive a message from user 2
    if (msgrcv(message_id, &message_buffer, sizeof(message_buffer.message_text), 3, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("User 3 received a message from User 2: %s\n", message_buffer.message_text);

    // Send a message to user 2
    message_buffer.message_type = 2;
    strcpy(message_buffer.message_text, "Hi there, User 2! This is User 3.");

    if (msgsnd(message_id, &message_buffer, sizeof(message_buffer.message_text), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    // Receive a message from user 1
    if (msgrcv(message_id, &message_buffer, sizeof(message_buffer.message_text), 3, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("User 3 received a message from User 1: %s\n", message_buffer.message_text);

    // Send a message to user 1
    message_buffer.message_type = 1;
    strcpy(message_buffer.message_text, "Hey User 1, it's User 3 here!");

    if (msgsnd(message_id, &message_buffer, sizeof(message_buffer.message_text), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    return 0;
}
