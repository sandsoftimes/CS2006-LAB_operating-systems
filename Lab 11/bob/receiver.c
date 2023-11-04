#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 512

struct msg_st {
    long int msg_type;
    char text[MAX_TEXT];
};

int main(int argc, char *argv[]) {
    int running = 1;
    int msgid;
    struct msg_st data;
    long int msg_from = 0;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Create message queue
    msgid = msgget((key_t)5678, 0666 | IPC_CREAT);
    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }

}

   

