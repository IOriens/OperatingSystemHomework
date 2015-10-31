#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

//fibonacci
void *fib(void *argv){
	int n = *(int *)argv;
	if(n>=0&&n<=10000){
		int arr[10000]={0};
		arr[0]=0;
		arr[1]=1;
		int i;
		for(i=2;i<=n;i++){
			arr[i]=arr[i-1]+arr[i-2];
		}
		// printf("The result is:%d\n",arr[n]);
		for(i=0;i<=n;i++){
			printf("		%d \n",arr[i]);
		}
	}else{
		printf("Out of Oprand Bound\n");
	}	
}

//primeNumbersBySieveOfEratosthenes 
void *primeNumbers(void *argv){
	int n = *(int *)argv;
	int num[1000] ={0};
	int i;
	for (i = 2; i <=n; ++i ) {       
		num[i] = 1;                       
	}
  // 按照埃拉托斯特尼筛法，将为基数的倍数的所有数标记为非素数。
	i = 2;
	while ( i * i  <= n ) {
		int c;
		int idx;
		for ( c = 2, idx = 2*i; idx <=n; ++c, idx = i * c) {
			num[idx] = 0;
		}
		do {
			++i;
		}while ( i * i <= n && num[i] == 0);
	}
	printf("primeNumbers less than or equal to %d:\n",n);
	for(i=0;i<=n;i++){
		if(num[i]==1){
			printf("%d\n",i);
		}
	}
}

int main(){
	  //prepare for process creation
	pid_t pid1;
	pid_t pid2;
	pid_t pid3;
	pid_t pid4;
	printf("FATHER-1:%d\n",getpid());

	  //prepare for thread creation
	pthread_t tid1;
	pthread_t tid2;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	//fork()
	pid1=fork();
	if(pid1==0){
		printf("CHILD-2:%d\n",getpid());
		int n=20;
		pthread_create(&tid1,&attr,fib,&n);
		pthread_create(&tid2,&attr,primeNumbers,&n);
		pthread_join(tid1,NULL);
		pthread_join(tid2,NULL);
		exit(0);
	}else{	  	

		pid2=fork();
		wait(NULL);		
	}

	if(pid2==0){
		printf("CHILD-3:%d\n",getpid());
		pid3=fork();
		if(pid3==0){
			printf("CHILD-4:%d\n",getpid());
			

			
		}else{
			pid4=fork();
			if(pid4==0){
				printf("CHILD-5:%d\n",getpid());
			}else{
				wait(NULL);
			}
		}
		exit(0);
	}else{
		wait(NULL);
	}




	return 0;
}
