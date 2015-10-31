#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
void sortnum(int arr[4][40000],int n,int index1){
	int i=0,j=0;
	for(j=1;j<n;j++){
		int key=arr[index1][j];		
		i=j-1;
		while(i>=0&&arr[index1][i]>key){
			arr[index1][i+1]=arr[index1][i];
			i--;
		}
		arr[index1][i+1]=key;	
	}
}

int main(){
	int xx=0;	
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
	

	for(xx=0;xx<4;xx++){
		pid_t pid;
		pid=fork();

		if(pid==0)
		{
			int i;

			sortnum(&unsorted[0],30000,xx);
			// for(i=0;i<5;i++){
			// 	printf("%d\n", unsorted[xx][i]);
			// }

		}else if(pid>0){
			wait(NULL);
			printf("CHILD %d PROCESS END \n", xx);
			exit(0);

		}
	}
		
	return 0;
}

