	#include <stdio.h>
	#include <pthread.h>


//用于线程参数的传递
struct parameters
{
	int idx;
	int **arr;
};

//插入排序算法实现
void sortnum(int **arr,int n,int index1){
	int i=0,j=0;
	
	for(j=1;j<n;j++){
		int key=*((int*)arr+40000*index1+j);
		i=j-1;
		while(i>=0&&(*((int*)arr+40000*index1+i))>key){
			(*((int*)arr+40000*index1+i+1))=(*((int*)arr+40000*index1+i));
			i--;
		}		
		*((int*)arr+40000*index1+i+1)=key;	
	}
}

//多线程的Runner
void *runner(void* param){
	struct parameters newparam= *(struct parameters *)param;
	int i;
	int idx=newparam.idx;	
	sortnum(newparam.arr,30000,idx);
	// for(i=0;i<5;i++){
	// 	printf("%d\n",(*((int*)newparam.arr+40000*idx+i)));
	// 	//(*((int*)newparam.arr+40000*idx+i))
	// }
	pthread_exit(0);
}

int main(){

	int xx=0;

	//准备将要排序的数组
	int unsorted[4][40000];
	int i1=0,j1=0;
	FILE *fp;
	if((fp=fopen("inpu.txt","rb"))==NULL){
		printf("Cannot read file\n");				
	}
	for(i1=0;i1<30000;i1++){
		fscanf(fp,"%d",&unsorted[0][i1]);
	}
	fclose(fp);
	for(i1=1;i1<4;i1++){
		for(j1=0;j1<30000;j1++){
			unsorted[i1][j1]=unsorted[0][j1];
		}
		printf("COPY_COMPLETED\n");	
	}

	//准备传入函数的参数
	struct parameters params[4];
	int cir0827=0;
	for(cir0827=0;cir0827<4;cir0827++){
		params[cir0827].idx=cir0827;
		params[cir0827].arr= (int **)unsorted;
	}

	//创建线程	
	pthread_t tid[4];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	int cir0830;
	for(cir0830=0;cir0830<4;cir0830++){
		pthread_create(&tid[cir0830],&attr,runner, (void *) & params[cir0830]);	
	}

	//线程合并
	for(cir0830=0;cir0830<4;cir0830++){
		pthread_join(tid[cir0830],NULL);
	}
	return 0;
}

	