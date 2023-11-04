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
} 
Message;
int main() {
    int msgid;
    key_t key = ftok("chat_app", 1); 
    if ((msgid = msgget(key, 0666 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }
    Message msg;
    msg.mtype = 1; 
    while (fgets(msg.mtext, MAX_TEXT_LENGTH, stdin) != NULL) {
        msg.mtext[strcspn(msg.mtext, "\n")] = 0;
        if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
    }
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }
    return 0;
}
