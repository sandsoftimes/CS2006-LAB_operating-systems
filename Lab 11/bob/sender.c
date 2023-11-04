#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 1020

struct msg_st {
    long int msg_type;
    char text[MAX_TEXT];
};

int main(int argc, char *argv[]) {
    int running = 1;
    int msgid;
    struct msg_st data;
    long int msg_to = 0;
    char msg_text[MAX_TEXT];

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <username> <receiver_username>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

  
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    
    data.msg_type = 1;
    sprintf(data.text, "%s", argv[1]); 

    printf("Welcome, %s! You are now connected to the chat.\n", argv[1]);
    printf("Type a message and press Enter to send it.\n\n");

    while (running) {
       

        printf("> ");
        fgets(msg_text, MAX_TEXT, stdin);


        sprintf(data.text, "%s: %s", argv[1], msg_text);

  
        msg_to = msgget((key_t)5678, 0666 | IPC_CREAT);
        if (msg_to == -1) {
            fprintf(stderr, "msgget failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        if (msgsnd(msg_to, (void *)&data, MAX_TEXT, 0) == -1) {
            fprintf(stderr, "msgsnd failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        printf("Message sent.\n\n");

    
        if (strncmp(msg_text, "exit", 4) == 0) {
            running = 0;
        }
    }


    if (msgctl(msgid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "msgctl(IPC_RMID) failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

