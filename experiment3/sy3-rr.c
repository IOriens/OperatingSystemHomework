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
	int time1;
	int remain;
	int state;
}pcb;

pcb thread[N];
int total=0;
int slice=3;
int flag=1;
int waitTime=0;

void* child(void* vargp){
	int i = *(int*)vargp;
	
	// printf("%d============child\n",i);
	while(thread[i].remain>0){
		pthread_mutex_lock(&s[i]);
		pthread_mutex_lock(&cpu);					
		int i2=0;
		sleep(1.5);
		waitTime+=(total-thread[i].time1);
		for(i2=0;i2<slice;i2++){
			if(thread[i].remain<=0){
				total++;
				printf("ThreadId is:%d Round:%d Remain:%d\n",thread[i].num,total,thread[i].remain);
			}else{
				printf("ThreadId is:%d Round:%d Remain:%d\n",thread[i].num,total,thread[i].remain);
				total++;
				thread[i].remain--;	
			}
			thread[i].time1=total;			
		}		
		pthread_mutex_unlock(&cpu);
		pthread_mutex_unlock(&s[i]);
		sleep(1);
	}
	
	
}

void* father(void* vargp){
	srand(time(NULL));
	int i=0;
	for(i=0;i<N;i++){
		pthread_mutex_lock(&s[i]);
		thread[i].num=i;
		// thread[i].time1=rand()%5;
		thread[i].remain=rand()%15+1;
		thread[i].state=0;
		thread[i].time1=0;
	}

	for(i=0;i<N;i++){
		thread[i].state=1;
		pthread_mutex_unlock(&s[i]);
	}

	int inum[N];
	int it1=0;
	for(it1=0;it1<N;it1++){
		inum[it1]=it1;
	}

	for(it1=0;it1<N;it1++){		
		pthread_create(&cid[it1],NULL,child,(void*)(&inum[it1]));		
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