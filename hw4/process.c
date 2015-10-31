#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
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
	int xx=0;
	for(xx=0;xx<3;xx++){
		pid_t pid;
		pid=fork();
		if(pid==0)
		{
			if(xx==2){
				printf("finish");
			}			
		}else if(pid>0){
			/*if(xx==1){
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
					printf("CH%d\n", unsorted[i]);
				}
//				exit(0);
			}*/		
			if(xx==2){
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
					printf("CH%d\n", unsorted[i]);
				}
				exit(0);
			}
				
		}
	}	
	return 0;
}

