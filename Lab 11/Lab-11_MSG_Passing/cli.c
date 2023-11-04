#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

#define MSGSZ 128

typedef struct msgbuf {
    long mtype;
    char mtext[MSGSZ];
} message_buf;

int main()
{
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    message_buf sbuf;
    message_buf rbuf;
    size_t buf_length;

    // create message queue for this user
    key = getpid(); // use PID as key to ensure unique message queue
    msqid = msgget(key, msgflg);

    // check if message queue was successfully created
    if (msqid == -1) {
        perror("msgget");
        return 1;
    }

    // connect to server message queue
    key = 0; // key 0 indicates the server message queue
    int server_msqid = msgget(key, msgflg);

    // check if server message queue was successfully created
    if (server_msqid == -1) {
        perror("msgget");
        return 1;
    }

    // main loop for sending and receiving messages
    while (1) {
        // send message
        printf("Enter message: ");
        fgets(sbuf.mtext, MSGSZ, stdin);
        sbuf.mtype = getpid(); // messages sent to server have type of this user's PID
        buf_length = strlen(sbuf.mtext) + 1;
        msgsnd(server_msqid, &sbuf, buf_length, IPC_NOWAIT);

        // receive message
        if (msgrcv(msqid, &rbuf, MSGSZ, 1, IPC_NOWAIT) != -1) {
            printf("Received message: %s", rbuf.mtext);
        }
    }

    return 0;
}
