	#include <stdio.h>
	#include <pthread.h>

	void *runner(void *param);

	void sortnum(int *arr,int n){
		int i=0,j=0;
		for(j=1;j<n;j++){
			int key=arr[j];		
			i=j-1;
			while(i>=0&&arr[i]>key){
				arr[i+1]=arr[i];
				i--;
			}
			arr[i+1]=key;	
		}
	}

	int main(){
		clock_t start,end;
		start=clock();

		int xx=0;

			pthread_t tid1;
			pthread_t tid2;
			pthread_t tid3;
			pthread_t tid4;
			pthread_attr_t attr;


			pthread_attr_init(&attr);
			pthread_create(&tid1,&attr,runner,NULL);
			pthread_create(&tid2,&attr,runner,NULL);
			pthread_create(&tid3,&attr,runner,NULL);
			pthread_create(&tid4,&attr,runner,NULL);
			pthread_join(tid1,NULL);
			pthread_join(tid2,NULL);
			pthread_join(tid3,NULL);
			pthread_join(tid4,NULL);
		end=clock();
		double timesp=(double)(end-start)/CLOCKS_PER_SEC;
		printf("TIME SPENT:%f\n",timesp);
		//printf(end-start);
		return 0;
	}

	void *runner(void *param){
		FILE *fp;
		if((fp=fopen("inpu.txt","rb"))==NULL){
			printf("Cannot read file\n");		
		}
		int unsorted[40000]={0},i;
		for(i=0;i<30000;i++){
			fscanf(fp,"%d",&unsorted[i]);
		}
		fclose(fp);

		sortnum(unsorted,30000);
		for(i=0;i<5;i++){
			printf("%d\n", unsorted[i]);
		}
		pthread_exit(0);
	}
