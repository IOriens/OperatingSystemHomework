#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define N 5

sem_t room;
sem_t chopstick[N];
sem_t phil[N];
pthread_t id[N];
int t=1;
int last;
void* philosopher(void* vargp)
{
	int i=*(int*)vargp;
	srand(time(NULL));
	while(1)
	{

		int j;
		sem_wait(&phil[i]);
		last=rand()%N;
		while(last==i){
			last=rand()%N;
		}
		sem_post(&phil[last]);
		sleep(1);

		if(i%2==1){
			sem_wait(&chopstick[i]); //请求左手边的筷子
			printf("philosopher %d get left chopstick %d in time %d\n",i,i,t);
			t++;
			
			sem_wait(&chopstick[(i+1)%5]); //请求右手边的筷子
			printf("philosopher %d get right chopstick %d in time %d\n",i,(i+1)%5,t);
			t++;
			printf("philosopher %d eat in time %d\n",i,t);
			t++;

			sem_post(&chopstick[(i+1)%5]); //释放右手边的筷子
			printf("philosopher %d release right chopstick %d in time %d\n",i,i,t);
			t++;

			sem_post(&chopstick[i]); //释放左手边的筷子
			printf("philosopher %d release left chopstick %d in time %d\n",i,i,t);
			t++;
		}else{
						
			sem_wait(&chopstick[(i+1)%5]); //请求右手边的筷子
			printf("philosopher %d get right chopstick %d in time %d\n",i,(i+1)%5,t);
			t++;

			sem_wait(&chopstick[i]); //请求左手边的筷子
			printf("philosopher %d get left chopstick %d in time %d\n",i,i,t);
			t++;

			printf("philosopher %d eat in time %d\n",i,t);
			t++;			

			sem_post(&chopstick[i]); //释放左手边的筷子
			printf("philosopher %d release left chopstick %d in time %d\n",i,i,t);
			t++;

			sem_post(&chopstick[(i+1)%5]); //释放右手边的筷子
			printf("philosopher %d release right chopstick %d in time %d\n",i,i,t);
			t++;
		}
		
	
		sleep(2);
		last=i;
	}
}

int main(){
	int i=0;
	sem_init(&room,0,N);
	for(i=0;i<N;i++){
		sem_init(&chopstick[i],0,1);
		sem_init(&phil[i],0,1);
	}
	int n[N];
	for(i=0;i<N;i++){
		n[i]=i;
	}	
	pthread_create(&id[0],NULL,philosopher,(void*)(&n[0]));
	pthread_create(&id[1],NULL,philosopher,(void*)(&n[1]));
	pthread_create(&id[2],NULL,philosopher,(void*)(&n[2]));
	pthread_create(&id[3],NULL,philosopher,(void*)(&n[3]));
	pthread_create(&id[4],NULL,philosopher,(void*)(&n[4]));
	for(i=0;i<N;i++){
		pthread_join(id[i],NULL);
	}
	return 0;
}
