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

    // User authentication server
    key = ftok("msgqueue.txt", 'A');
    msgid = msgget(key, 0666 | IPC_CREAT);
    printf("User authentication server started\n");

    while(1) {
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        sscanf(message.mtext, "%s %s", user_id, auth_token);
        printf("User authentication server: Received user ID %s with auth token %s\n", user_id, auth_token);

        // Authenticate user
        if(strcmp(user_id, "user1") == 0 && strcmp(auth_token, "token1") == 0) {
            message.mtype = 2;
            strcpy(message.mtext, "Authentication successful");
        } else if(strcmp(user_id, "user2") == 0 && strcmp(auth_token, "token2") == 0) {
            message.mtype = 2;
            strcpy(message.mtext, "Authentication successful");
        } else if(strcmp(user_id, "user3") == 0 && strcmp(auth_token, "token3") == 0) {
            message.mtype = 2;
            strcpy(message.mtext, "Authentication successful");
        } else if(strcmp(user_id, "user4") == 0 && strcmp(auth_token, "token4") == 0) {
            message.mtype = 2;
            strcpy(message.mtext, "Authentication successful");
        } else {
            message.mtype = 2;
            strcpy(message.mtext, "Authentication failed");
        }

        msgsnd(msgid, &message, sizeof(message), 0);
    }

    return 0;
}

