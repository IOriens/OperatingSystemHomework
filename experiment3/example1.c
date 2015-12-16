#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N_Tom 3
#define N_Bob 5
#define T_SLEEP 1
#define B_SLEEP 1

pthread_t Tid[N_Tom],Bid[N_Bob];
pthread_mutex_t writeLock = PTHREAD_MUTEX_INITIALIZER;
int data=0;

void * Bob(void * in){
	while(1){
		pthread_mutex_lock(&writeLock);
		data++;
		printf("I am Bob, data is:%d\n",data);
		pthread_mutex_unlock(&writeLock);
		sleep(B_SLEEP);
	}
	pthread_exit((void *) 0);
}

void * Tom(void * in){
	while(1){
		pthread_mutex_lock(&writeLock);
		data++;
		printf("I am Tom,data is:%d\n",data);
		pthread_mutex_unlock(&writeLock);
		sleep(T_SLEEP);
	}
	pthread_exit((void *) 0);
}

int main(){
	int i=0;
	for(i=0;i<N_Tom;i++){
		pthread_create(&Tid[i],NULL,Tom,NULL);
	}
	for(i=0;i<N_Bob;i++){
		pthread_create(&Bid[i],NULL,Bob,NULL);
	}
	while(1){
		sleep(10);
	}

	return 0;
}