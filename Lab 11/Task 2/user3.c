#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

#define MAX_MSG_SIZE 100
struct msgbuf {
    long mtype;
    char mtext[MAX_MSG_SIZE];
};
int main() {
    key_t key;
    int msgid;
    struct msgbuf message;
    // Create key
    if ((key = ftok("msgq.txt", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }
    // Connect to message queue
    if ((msgid = msgget(key, 0666)) == -1) {
        perror("msgget");
        exit(1);
    }
    // Send message to User 1
    message.mtype = 1;
    strcpy(message.mtext, "Hello User 1, this is User 3!");
    if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    // Receive message from User 1
    if (msgrcv(msgid, &message, MAX_MSG_SIZE, 2, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }
    printf("User 3 received message: %s\n", message.mtext);
    // Send message to User 2
    message.mtype = 3;
    strcpy(message.mtext, "Hello User 2, this is User 3!");
    if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    // Receive message from User 2
    if (msgrcv(msgid, &message, MAX_MSG_SIZE, 4, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }
    printf("User 3 received message: %s\n", message.mtext);
    // Send message to User 1 again
    message.mtype = 5;
    strcpy(message.mtext, "Hello again User 1, this is User 3!");
    if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    // Receive message from User 1 again
    if (msgrcv(msgid, &message, MAX_MSG_SIZE, 6, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }
    printf("User 3 received message: %s\n", message.mtext);
    // Disconnect from message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }
    
    return 0;
}