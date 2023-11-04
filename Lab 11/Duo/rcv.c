#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT_LENGTH 1024

typedef struct message {
    long mtype;
    char mtext[MAX_TEXT_LENGTH];
} Message;

int main() {
    int msgid;
    key_t key = ftok("chat_app", 1); // create a key for the message queue

    // get the existing message queue with the key
    if ((msgid = msgget(key, 0666)) == -1) {
        perror("msgget");
        exit(1);
    }

    Message msg;

    // receive messages from the message queue and print them to the console
    while (1) {
        // receive the message from the message queue
        if (msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        // print the message to the console
        printf("Received message: %s\n", msg.mtext);
    }

    return 0;
}
