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
	char data[10];
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
	if(fork())	
	{
		while(1)
		{
			v1.mtype=2;
			printf("ali1: ");
			scanf(" %[^\n]s",s);
			strcpy(v1.data,s);
			msgsnd(id,&v1,strlen(v1.data)+1,0); 
		}
	}
	else
	{
		while(1)
		{
			msgrcv(id,&v2,sizeof(v2),3,0);  
			printf("\rali2: %s\n",v2.data);
			printf("ali1: ");
			fflush(stdout); 
		}
	}
}
