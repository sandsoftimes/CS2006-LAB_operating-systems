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

    if ((key = ftok("msgq.txt", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }
   
    if ((msgid = msgget(key, 0666)) == -1) {
        perror("msgget");
        exit(1);
    }
    
    message.mtype = 1;
    strcpy(message.mtext, "Hello User 1, this is User 3!");
    if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
   
    if (msgrcv(msgid, &message, MAX_MSG_SIZE, 2, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }
    printf("User 3 received message: %s\n", message.mtext);
    
    message.mtype = 3;
    strcpy(message.mtext, "Hello User 2, this is User 3!");
    if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    
    if (msgrcv(msgid, &message, MAX_MSG_SIZE, 4, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }
    printf("User 3 received message: %s\n", message.mtext);
    
    message.mtype = 5;
    strcpy(message.mtext, "Hello again User 1, this is User 3!");
    if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    
    if (msgrcv(msgid, &message, MAX_MSG_SIZE, 6, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }
    printf("User 3 received message: %s\n", message.mtext);
    
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }
    
    return 0;
}
