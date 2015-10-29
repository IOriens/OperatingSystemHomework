#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

//定义缓存区大小
typedef int buffer_item;
#define BUFFER_SIZE 5

//定义互斥锁和empty、full信号量
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

//定义缓冲区
buffer_item buffer[BUFFER_SIZE];
buffer_item front=0,rear=0;


//插入物品
int insert_item(buffer_item item){
	int i=0;
	if((rear+1)%BUFFER_SIZE==front)
		return -1;
	buffer[rear]=item;
	rear=(rear+1)%(BUFFER_SIZE);
	return 0;
}

//移除物品
int remove_item(buffer_item *item){
	if(front=rear)
		return -1;
	*item=buffer[front];
	front=(front+1)%BUFFER_SIZE;
	return 0;
}

//生产者
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

//消费者
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

	//判断输入参数个数是否符合要求
	if(argc != 4){
		printf("Use Correct arguments\n");
		return 0;
	}

	//解析传入的参数
	int sleeptime=atoi(argv[1]); 
	int pthnum=atoi(argv[2]);
	int cthnum=atoi(argv[3]);

	//输出解析的参数
	printf("Sleep Time:%d\n",sleeptime);
	printf("Producer:%d,Consumer:%d\n",pthnum,cthnum);

	//初始化缓冲区
	int i=0;
	buffer_item initi=0;
	for(i=0;i<BUFFER_SIZE;i++){
		buffer[i]=initi;
	}

	//定义生产者消费者线程数组
	pthread_t pth[pthnum+10];
	pthread_t cth[cthnum+10];

	//初始化多线程属性
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	//初始化信号量以及互斥锁
	sem_init(&empty,0,5);
	sem_init(&full,0,0);
	pthread_mutex_init(&mutex,NULL);

	//创建多个线程
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

	//使主进程进入睡眠状态
	sleep(sleeptime);
	return 0;
}
