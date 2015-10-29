#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>



typedef int buffer_item;
#define BUFFER_SIZE 5


pthread_mutex_t mutex;

sem_t empty;
sem_t full;


buffer_item buffer[BUFFER_SIZE];
int head=0,end=0;

int insert_item(buffer_item item){
	int i=0;
	for(i=0;i<BUFFER_SIZE;i++){
		if(buffer[i]==0){
			buffer[i]=item;
			return 0;
		}
	}
	return -1;
}

int remove_item(buffer_item *item){
	int i=0;
	for(i=0;i<BUFFER_SIZE;i++){
		if(buffer[i]>0){
			*item=buffer[i];
			buffer[i]=0;
			return 0;
		}
	}
	return -1;
}

void *producer(void *param){
	buffer_item item;
	srand(time(NULL));
	int sleeptime=rand()%5;
	while(1){
		sleep(sleeptime);
		item=rand();

		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		if(insert_item(item))
			printf("report error condition");
		else
			printf("++Pruduced by %d : %d\n",(int)pthread_self(),item);
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	}
}

void *consumer(void *param){
	buffer_item item;
	srand(time(NULL));
	int sleeptime=rand()%5;
	while(1){	
		sleep(sleeptime);

		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		if(remove_item(&item))
			printf("report error condition");
		else
			// printf("Consumed %d\n",item);
			printf("--Consumed by %d : %d\n",(int)pthread_self(),item);
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
	}
}

int main(int argc,char *argv[]){

	if(argc<4){
		printf("Use more arguments\n");
		return 0;
	}

	int sleeptime=atoi(argv[1]); 
	int pthnum=atoi(argv[2]);
	int cthnum=atoi(argv[3]);

	printf("Sleep Time:%d\n",sleeptime);
	printf("Producer:%d,Consumer:%d\n",pthnum,cthnum);

	int i=0;
	for(i=0;i<BUFFER_SIZE;i++){
		buffer[i]=0;
	}

	pthread_t pth[pthnum+10];
	pthread_t cth[cthnum+10];

	pthread_attr_t attr;
	pthread_attr_init(&attr);


	sem_init(&empty,0,5);
	sem_init(&full,0,0);
	pthread_mutex_init(&mutex,NULL);

	int j;
	for(i=0;i<pthnum;i++){
		pthread_create(&pth[i],&attr,producer,NULL);
		printf("++Producer thread %d created!\n", i);
	}
	for (j = 0; j< cthnum; ++j)
	{
		pthread_create(&pth[i],&attr,consumer,NULL);
		printf("--Consumer thread %d created!\n", j);
	}

	sleep(sleeptime);
	return 0;
}