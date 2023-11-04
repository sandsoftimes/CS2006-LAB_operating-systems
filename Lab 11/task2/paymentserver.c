#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_SIZE 1024

struct msgbuf {
    long mtype;
    char mtext[MSG_SIZE];
};

int main() {
    key_t key;
    int msgid;
    struct msgbuf message;
    char user_id[20];
    char auth_token[20];
    char payment_details[100];

    // Payment server
    key = ftok("msgqueue.txt", 'B');
    msgid = msgget(key, 0666 | IPC_CREAT);
    printf("Payment server started\n");

    while(1) {
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        sscanf(message.mtext, "%s %s %s", user_id, auth_token, payment_details);
        printf("Payment server: Received user ID %s with auth token %s and payment details %s\n", user_id, auth_token, payment_details);

        // Check user authentication
        message.mtype = 2;
        strcpy(message.mtext, user_id);
        msgsnd(msgid, &message, sizeof(message), 0);
        msgrcv(msgid, &message, sizeof(message), 3, 0);
        if(strcmp(message.mtext, "Authentication successful") != 0) {
            message.mtype = 4;
            strcpy(message.mtext, "Payment failed: User authentication failed");
            msgsnd(msgid, &message, sizeof(message), 0);
            continue;
        }

        // Process payment
        message.mtype = 2;
        strcpy(message.mtext, "Payment processing");
        msgsnd(msgid, &message, sizeof(message), 0);

        // Send payment details to recipient
        message.mtype = 3;
        strcpy(message.mtext, payment_details);
        msgsnd(msgid, &message, sizeof(message), 0);

        // Confirm payment to user
        message.mtype = 4;
        strcpy(message.mtext, "Payment successful");
        msgsnd(msgid, &message, sizeof(message), 0);
    }

    return 0;
}

