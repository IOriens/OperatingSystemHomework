#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define N 3
pthread_t fid[1],cid[N];
pthread_mutex_t cpu=PTHREAD_MUTEX_INITIALIZER,s[N]={PTHREAD_MUTEX_INITIALIZER,PTHREAD_MUTEX_INITIALIZER,PTHREAD_MUTEX_INITIALIZER};
typedef struct PCB{
	int num;
	int time1;
	int remain;
	int state;
}pcb;

pcb thread[3];
int total=0;

void* child(void* vargp){
	int i = *(int*)vargp;
	// if(i==1){
	// 	sleep(1);
	// }
	pthread_mutex_lock(&s[i]);
	pthread_mutex_lock(&cpu);
	while(thread[i].remain>0){
		printf("ThreadId is:%d %d\n",thread[i].num,total);
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

	int i0=0,i1=1,i2=2;
	pthread_create(&cid[0],NULL,child,(void*)(&i0));
	sleep(1);
	pthread_create(&cid[1],NULL,child,(void*)(&i1));
	pthread_create(&cid[2],NULL,child,(void*)(&i2));

	for(i=0;i<N;i++){
		pthread_join(cid[i],NULL);
	}
}

int main(){
	int i=0;
	pthread_create(&fid[i],NULL,father,(void*)(&i));
	pthread_join(fid[i],NULL);

	return 0;
}