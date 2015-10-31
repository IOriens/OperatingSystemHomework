#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	int fd[2],nbytes;
	pid_t childpid1;
	pid_t childpid2;
	char* string="ok";
	char readbuffer[80];

	pipe(fd);

	int w_fd=fd[1];
	int r_fd=fd[0];
	childpid1=fork();
	if(childpid1==0){
		close(r_fd);
		FILE *fp;
		fp=fopen("123.txt","w");
		fprintf(fp,"Text in 123.txt");
		fclose(fp);
		write(w_fd,string,strlen(string));		
		exit(0);
	}else{
		childpid2=fork();
		wait(NULL);
	}


	if(childpid2==0){
		close(w_fd);
		nbytes=read(r_fd,readbuffer,sizeof(readbuffer));
		char * str_2 = "ok"; 
		if(strcmp(readbuffer,str_2)==0){
			char ch;
			FILE *fp;
			fp=fopen("123.txt","r");
			while((ch = fgetc(fp)) != EOF)
				putchar(ch);
			printf("\n");
			fclose(fp);
		}		
		else
			printf("Communication Failed\n");
		exit(0);
	}else{
		wait(NULL);
	}	
	return 0;
}