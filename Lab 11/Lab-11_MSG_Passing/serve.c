#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

#define MSGSZ 128
#define MAX_USERS 10

typedef struct msgbuf {
    long mtype;
    char mtext[MSGSZ];
} message_buf;

int main()
{
    int msqid[MAX_USERS]; // message queue IDs for all users
    int msgflg = IPC_CREAT | 0666;
    key_t key[MAX_USERS];
    int num_users = 0;
    message_buf rbuf;

    while(num_users < MAX_USERS) {
        // create message queue for new user
        key[num_users] = num_users + 1; // keys should be unique for each message queue
        msqid[num_users] = msgget(key[num_users], msgflg);
        
        // check if message queue was successfully created
        if (msqid[num_users] == -1) {
            perror("msgget");
            return 1;
        }
        
        num_users++;
    }

    // server loop
    while (1) {
        for (int i = 0; i < num_users; i++) {
            if (msgrcv(msqid[i], &rbuf, MSGSZ, 1, IPC_NOWAIT) != -1) {
                // message received from user i
                for (int j = 0; j < num_users; j++) {
                    if (j != i) {
                        // relay message to all other users
                        msgsnd(msqid[j], &rbuf, sizeof(message_buf), IPC_NOWAIT);
                    }
                }
            }
        }
    }

    return 0;
}
