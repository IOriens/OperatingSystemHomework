#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

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
		printf("The result is:%d\n",n);
	}else{
		printf("Out of Oprand Bound\n");
	}	
}

//primeNumbersBySieveOfEratosthenes 
void *primeNumbers(void *argv){
	int n = *(int *)argv;
	char* num = (char*) malloc(sizeof(char) * n );
	int i;
	for (i = 2; i < n; ++i ) {       
		num[i] = TRUE;                       
	}
  // 按照埃拉托斯特尼筛法，将为基数的倍数的所有数标记为非素数。
	i = 2;
	while ( i * i  <= n ) {
		int c;
		int idx;
		for ( c = 2, idx = 2*i; idx < n; ++c, idx = i * c) {
			num[idx] = FALSE;
		}
		do {
			++i;
		}while ( i * i <= n && num[i] == FALSE);
	}
	printf("primeNumbers less than or equal to %d:\n",n);
	for(i=0;i<=n;i++){
		if(num[i]=true){
			printf("%d ",i);
		}
	}
}

int main(){
	  //prepare for process creation
	pid_t pid1;
	printf("FATHER-1:%d\n",getpid());

	  //prepare for thread creation
	pthread_t tid1;
	pthread_t tid2;
	pthread_attr_t attr;

	//fork()
	pid1=fork();
	if(pid1==0){
		printf("CHILD-1:%d\n",getpid());
		


	}else{	  	

		pid_t pid2=fork();
	}
	return 0;
}
