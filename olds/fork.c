#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int value=5;
int main(){
	int value=1;
	int i;
	for( i=0;i<5;i++){
		pid_t cpid=fork();

		if(cpid==0){
			value+=1;
			printf("CHILD_PID=%d\n",getpid());
			printf("CHILD_value=%d\n",value);
		}else if(cpid>0){
			wait(NULL);
			printf("PARENT_ID=%d,CURRENT_ID=%d,CHILDID=%d\n",getppid(),getpid(),cpid);
			printf("Parent_value=%d\n",value);
			exit(0);	
		}
	}
}
