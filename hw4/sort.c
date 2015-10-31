#include <stdio.h>

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
	FILE *fp;
	if((fp=fopen("inpu.txt","rb+"))==NULL){
		printf("Cannot read file\n");
		exit(1);
	}
	int unsorted[40000]={0},i;
	for(i=0;i<30000;i++){
		fscanf(fp,"%d",&unsorted[i]);
	}
	fclose(fp);
	
	sortnum(unsorted,30000);
	for(i=0;i<50;i++){
		printf("%d\n", unsorted[i]);
	}
	return 0;
}

