#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main(){
	srand(time(NULL));
	FILE *fp;
	if((fp=fopen("inpu.txt","wb+"))==NULL){
		printf("Cann't open file!");
		getchar();
		exit(1);
	}
	int i=0;
	for(i=0;i<30000;i++){
		fprintf(fp, "%d\n",rand()%100000);
	}
	fclose(fp);
	return 0;
}
