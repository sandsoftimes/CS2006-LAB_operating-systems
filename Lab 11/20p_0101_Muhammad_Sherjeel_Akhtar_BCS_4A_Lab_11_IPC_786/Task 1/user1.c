#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct msgbuf  
{
	long mtype;
	char data[30];
};
int main()
{
	char s[30];
	struct msgbuf v1,v2;
	int id;
	id=msgget(4,IPC_CREAT|0644);  
	if(id<0)
	{
		perror("msgget");
		return 0;
	}
	if(fork()==0)
	{
		while(1)
		{
			msgrcv(id,&v1,sizeof(v1),2,0);  
			printf("\rali2: %s\n",v1.data);
			printf("ali1: ");
			fflush(stdout);  
		}
	}
	else
	{
		while(1)
		{
			v2.mtype=3;
			printf("ali1: ");
			scanf(" %[^\n]s",s);
			strcpy(v2.data,s);
			msgsnd(id,&v2,strlen(v2.data)+1,0);  
		}
	}
}
