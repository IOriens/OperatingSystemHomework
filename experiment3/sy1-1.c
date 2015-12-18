#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

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

void* child(void* vargp){
	int i = *(int*)vargp;
	
	// printf("%d============child\n",i);
	
	pthread_mutex_lock(&s[i]);
	pthread_mutex_lock(&cpu);	
	if(i==1){
		sleep(1);
	}
	while(thread[i].remain>0){
		printf("ThreadId is:%d Round:%d Remain:%d\n",thread[i].num,total,thread[i].remain);
		total++;
		thread[i].remain--;		
	}	
	pthread_mutex_unlock(&cpu);
	pthread_mutex_unlock(&s[i]);

	
	
}

void* father(void* vargp){
	int i=0;
	for(i=0;i<N;i++){
		pthread_mutex_lock(&s[i]);
		thread[i].num=i;
		thread[i].time1=2;
		thread[i].remain=2;
		thread[i].state=0;
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
		
		if(it1==0){
			sleep(1);		
		}	
	}
	// sleep(1);	
	for(i=0;i<N;i++){
		pthread_join(cid[i],NULL);
	}
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