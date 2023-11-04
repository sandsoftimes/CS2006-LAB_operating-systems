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
    int msgid, chatid, paymentid;
    struct msgbuf message;
    char user_id[20];
    char auth_token[20];
    char recipient_id[20];
    char chat_message[MSG_SIZE];
    char choice[10];

    // User authentication server
    key = ftok("msgqueue.txt", 'A');
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Authenticate user
    while(1) {
        printf("Enter user ID: ");
        scanf("%s", user_id);
        printf("Enter auth token: ");
        scanf("%s", auth_token);

        message.mtype = 1;
        sprintf(message.mtext, "%s %s", user_id, auth_token);
        msgsnd(msgid, &message, sizeof(message), 0);

        msgrcv(msgid, &message, sizeof(message), 2, 0);
        if(strcmp(message.mtext, "Authentication successful") == 0) {
            printf("Authentication successful\n");
            break;
        } else {
            printf("Authentication failed\n");
        }
    }

    // Prompt user to chat or access payment details
    while(1) {
        printf("Enter 'c' to chat or 'p' to access payment details: ");
        scanf("%s", choice);
        if(strcmp(choice, "c") == 0) {
            // User chat client
            key = ftok("msgqueue.txt", 'B');
            chatid = msgget(key, 0666 | IPC_CREAT);
            printf("Connected to chat server\n");

            // Send chat messages to other user
            while(1) {
                printf("Enter recipient user ID: ");
                scanf("%s", recipient_id);
                printf("Enter chat message: ");
                scanf(" %[^\n]s", chat_message);

                message.mtype = 1;
                sprintf(message.mtext, "%s %s %s", user_id, recipient_id, chat_message);
                msgsnd(chatid, &message, sizeof(message), 0);

                msgrcv(chatid, &message, sizeof(message), 2, 0);
                printf("User %s: %s\n", message.mtext, chat_message);
            }
        } else if(strcmp(choice, "p") == 0) {
            // User payment client
            key = ftok("msgqueue.txt", 'C');
            paymentid = msgget(key, 0666 | IPC_CREAT);
            printf("Connected to payment server\n");

            // Access payment details
            message.mtype = 1;
            sprintf(message.mtext, "%s", user_id);
            msgsnd(paymentid, &message, sizeof(message), 0);

            msgrcv(paymentid, &message, sizeof(message), 2, 0);
            printf("User %s payment details: %s\n", user_id, message.mtext);
        } else {
            printf("Invalid choice\n");
        }
    }
    
    return 0;
}

