#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define N 20

pthread_t fid[1],cid[N];
pthread_mutex_t cpu=PTHREAD_MUTEX_INITIALIZER,s[N];
typedef struct PCB{
	int num;	
	int remain;
	int state;
	int prio;	
}pcb;

typedef struct PCBTEMP{
	int prio;
	int index;
}temp;

pcb thread[N],nThread[N];
temp pcbIns[N];
int total=0;

int first=0;
int waitTime=0;
void insertionSort(n){
	int j=1;
	for(j=1;j<n;j++){
		int key=pcbIns[j].prio;
		int i=j-1;
		while((i>=0)&&(pcbIns[i].prio>key)){
			pcbIns[i+1].prio=pcbIns[i].prio;
			int tempIdx=pcbIns[i+1].index;
			pcbIns[i+1].index=pcbIns[i].index;
			pcbIns[i].index=tempIdx;
			i--;
		}
		pcbIns[i+1].prio=key;		
	}
}
void* child(void* vargp){
	int i = *(int*)vargp;		
	pthread_mutex_lock(&s[i]);
	pthread_mutex_lock(&cpu);	
	waitTime+=total;
	while(nThread[i].remain>0){
		printf("ThreadId is:%d Round:%d Remain:%d Prio:%d \n",nThread[i].num,total,nThread[i].remain,nThread[i].prio);		
		total++;
		nThread[i].remain--;		
	}	
	pthread_mutex_unlock(&cpu);
	pthread_mutex_unlock(&s[i]);
}

void* father(void* vargp){
	srand(time(NULL));
	int i=0;
	int it1=0;
	for(i=0;i<N;i++){
		pthread_mutex_lock(&s[i]);
		thread[i].num=i;
		thread[i].remain=rand()%5+1;
		thread[i].prio=rand()%5+1;
		thread[i].state=0;
		pcbIns[i].prio=thread[i].prio;
		pcbIns[i].index=i;
	}

	for(i=0;i<N;i++){
		thread[i].state=1;
		pthread_mutex_unlock(&s[i]);
	}

	insertionSort(N);
	first=pcbIns[0].index;
	for(it1=0;it1<N;it1++){		
		nThread[it1]=thread[pcbIns[N-it1-1].index];		
	}

	int inum[N];
	for(it1=0;it1<N;it1++){
		inum[it1]=it1;
	}

	for(it1=0;it1<N;it1++){
		pthread_create(&cid[it1],NULL,child,(void*)(&inum[it1]));			
		sleep(1);				
	}
	
	for(i=0;i<N;i++){		
		pthread_join(cid[i],NULL);
	}

	printf("\nAverage WaitTime = %f s\n",waitTime*1.0/N);
}

int main(){
	int i=0,j=0;
	
	for(j=0;j<N;j++){
		s[j]=cpu;
	}

	pthread_create(&fid[i],NULL,father,(void*)(&i));
	pthread_join(fid[i],NULL);

	return 0;
}