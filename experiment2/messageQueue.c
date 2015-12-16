#include <sys/msg.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#define MAX 100

struct msgbuff
{
	long mtype;
	char data[MAX];
};

int main(){
	int pid1,pid2;

	key_t key;
	if((key=ftok("/tmp",'g'))<0){
		printf("Getting key error!\n");
		return -1;
	}

	int msgid;

	if((msgid=msgget(key,IPC_CREAT|0666))==-1){
		printf("msg queue create error\n");
		return -1;
	}

	pid1=fork();
	if(pid1==0){
		printf("Welcome to child process 1\n Sending the message.....\n");
		sleep(1);
		struct msgbuff msg1;
		msg1.mtype=getppid();
		strcpy(msg1.data,"ok");
		if(msgsnd(msgid,&msg1,sizeof(msg1.data),0)<0){
			printf("Sending error\n");
			exit(1);
		}else{
			FILE *fp;
			fp=fopen("123.txt","w");
			fprintf(fp,"Shall I compare thee to a summer's day?\nThou art more lovely and more temperate.\n");
			fclose(fp);
			exit(0);
		}
	}else{
		
		pid2=fork();
		wait(NULL);
	}

	if(pid2==0){
		printf("Welcome to child process 2\n Receiving the message....\n");
		sleep(3);
		struct msgbuff msg2;
		if(msgrcv(msgid,&msg2,MAX,getppid(),0)<0){
			printf("Receiving error!!!\n");
			exit(1);
		}else{
			printf("Receiving complete\n");
			printf("The message is : %s \n",msg2.data);
			if(strcmp(msg2.data,"ok")==0){
				char ch;
				FILE *fp;
				fp=fopen("123.txt","r");
				while((ch = fgetc(fp)) != EOF)
					putchar(ch);
				printf("\n");
				fclose(fp);	
			}
		}
		exit(0);
	}else{
		wait(NULL);
	}
	return 0;
}