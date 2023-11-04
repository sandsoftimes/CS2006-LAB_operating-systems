#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<string.h>
// #define MSGSZ 128
#define MSGSZ2 128
// typedef struct msgbuf {
    // long mtype;
    // char mtext[MSGSZ];
// } message_buf;
typedef struct msgbuf2{
    long mtype;
    char mtext[MSGSZ2];
}message_buf2;
int main()
{
    int msqid2;
    // int msqid;
    // int msgflg = IPC_CREAT | 0666;
    int msgflg2=IPC_CREAT | 0666;
    // key_t key;
    key_t key2;
    // message_buf sbuf;
    message_buf2 sbuf2;
    // size_t buf_length;
    size_t buf_legth2;
    // key = 1234;
    key2=1234;
    // msqid = msgget(key, msgflg );
    msqid2=msgget(key2,msgflg2);
    sbuf2.mtype=1;
    // sbuf.mtype = 1;
    // strcpy(sbuf.mtext, "Im finished now good bye");
    strcpy(sbuf2.mtext,"I hope u are doing good");
    // buf_length = strlen(sbuf.mtext) + 1 ;
    buf_legth2=strlen(sbuf2.mtext);
    msgsnd(msqid2,&sbuf2,buf_legth2,IPC_NOWAIT);
    // msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT);
    return 0;
}