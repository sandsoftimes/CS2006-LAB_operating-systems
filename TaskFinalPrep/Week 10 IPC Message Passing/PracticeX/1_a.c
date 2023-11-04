#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
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
    // key_t key;
    key_t key2;
    // message_buf rbuf;
    message_buf2 rbuf;
    // key = 1234;
    key2=1234;
    // msqid = msgget(key, 0666);
    msqid2=msgget(key2,0666);
    msgrcv(msqid2,&rbuf,MSGSZ2,1,0);
    // msgrcv(msqid, &rbuf, MSGSZ, 1, 0);
    // printf("%s\n", rbuf.mtext);
    printf("%s\n",rbuf.mtext);
    return 0;
}