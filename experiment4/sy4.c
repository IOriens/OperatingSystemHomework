#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


//W = Num of WorkLoad
#define W  1000000
//P = Num of Page
#define PNUM  50000

int P=100;
int workLoad[W]={0};
int pageNumArr[5]={100,500,1000,2000,5000};
int page[PNUM];
int CLOCKPAGE[PNUM];
int RW=0;//Real Num of WorkLoad
int max=0;
int min=99999999;
int findPage(int pageNum){
	int it;
	for(it=0;it<P;it++){
		if(pageNum==page[it]){
			// printf("success at %d \n",it);
			return 1;		
		}		
		if(page[it]==-1){			
			return 0;		
		}
	}
	return 0;
}

int findPage2(int pageNum,int* idx){
	int it;
	for(it=0;it<P;it++){
		if(pageNum==page[it]){
			// printf("success at %d \n",it);
			*idx=it;
			return 1;		
		}		
		if(page[it]==-1){			
			return 0;		
		}
	}
	return 0;
}

void initializePage(){
	int it0=0;
	for(it0;it0<P;it0++){
		page[P]=-1;
		CLOCKPAGE[P]=0;
	}
}

void FIFO(){
	printf("===========*.*===========\n" );
	printf("\tAlgorithm = FIFO\n");
	printf("\tPageNUM = %d\n",P);
	printf("  =========*.*=========  \n" );
	int pageLost=0;	
	int pageLostArr[1000];
	int pageLostArrLen=0;
	int divBaseForLostArr=50000;
	int i=0;
	int curr=0;
	for(i=0;i<RW;i++){

		if(findPage(workLoad[i])==1){
			//find success

		}else{
			pageLost++;
			page[curr]=workLoad[i];
			curr=(curr+1)%P;
		}
		if(i%divBaseForLostArr==0 && i>0){
			pageLostArr[pageLostArrLen]=pageLost;
			pageLostArrLen++;
			printf("Till %d the page lost rate is %f\n",i,pageLost*1.0/i);
		}
	}

	printf("\tPage Lost = %d\n\tPage Lost Rate = %f \n", pageLost,pageLost*1.0/RW );
	printf("===========*.*===========\n\n" );
}

void CLOCK(){
	printf("===========*.*===========\n" );
	printf("\tAlgorithm = CLOCK\n");
	printf("\tPageNUM = %d\n",P);
	printf("  =========*.*=========  \n" );
	int pageLost=0;	
	int pageLostArr[1000];	
	int pageLostArrLen=0;
	int divBaseForLostArr=50000;
	int i=0;
	int curr=0;
	int findOutCome=0;
	for(i=0;i<RW;i++){

		if(findPage2(workLoad[i],&findOutCome)==1){
			//find success
			// printf("%d\n",findOutCome);
			CLOCKPAGE[findOutCome]=1;
		}else{
			int tempCurr=curr;
			while(CLOCKPAGE[curr]==1) {
				CLOCKPAGE[curr]=0;
				curr=(curr+1)%P;
				// if(curr==tempCurr)
					// break;
				//IMP
			}
			// printf("=====================================" );
			pageLost++;
			page[curr]=workLoad[i];
			CLOCKPAGE[curr]=0;
			curr=(curr+1)%P;
		}
		if(i%divBaseForLostArr==0 && i>0){
			pageLostArr[pageLostArrLen]=pageLost;
			pageLostArrLen++;
			printf("Till %d the page lost rate is %f\n",i,pageLost*1.0/i);
		}
	}

	printf("\tPage Lost = %d\n\tPage Lost Rate = %f \n", pageLost,pageLost*1.0/RW );
	printf("===========*.*===========\n\n" );
}

void LRU(){
	printf("===========*.*===========\n" );
	printf("\tAlgorithm = LRU\n");
	printf("\tPageNUM = %d\n",P);
	printf("  =========*.*=========  \n" );
	int pageLost=0;	
	int pageLostArr[1000];	
	int pageLostArrLen=0;
	int divBaseForLostArr=50000;
	int i=0;	
	int findOutCome=0;
	for(i=0;i<RW;i++){

		if(findPage2(workLoad[i],&findOutCome)==1){
			//find success
			// printf("%d\n",findOutCome);
			CLOCKPAGE[findOutCome]++;
		}else{
			int i20=0;
			int idxLRU=0;
			int minLRU=INT_MAX;
			for(i20=0;i20<P;i20++){
					if(CLOCKPAGE[i20]<minLRU){
						minLRU=CLOCKPAGE[i20];
						idxLRU=i20;
					}
			}			
			
			pageLost++;
			page[idxLRU]=workLoad[i];
			for(i20=0;i20<P;i20++){
					if(i20==idxLRU){
						CLOCKPAGE[i20]++;
					}else{
						CLOCKPAGE[i20]--;
					}
			}	
		}
		if(i%divBaseForLostArr==0 && i>0){
			pageLostArr[pageLostArrLen]=pageLost;
			pageLostArrLen++;
			printf("Till %d the page lost rate is %f\n",i,pageLost*1.0/i);
		}
	}

	printf("\tPage Lost = %d\n\tPage Lost Rate = %f \n", pageLost,pageLost*1.0/RW );
	printf("===========*.*===========\n\n" );
}


int main(){

	//Read workload to array 'workLoad'
	FILE *pRead;
	char baseDir[] ="WorkLoad/workload";
	int wl=2;
	char newDir[10];	
	sprintf(newDir,"%d",wl);
	strcat(baseDir,newDir);	 
	printf("Reading = %s\n", baseDir);
	FILE *fin,*fout;

	fin=fopen(baseDir,"rb");
	
	if(NULL==fin){
		printf("File Read Fail");
	}

	while(fscanf(fin,"%d",&workLoad[RW])!=EOF){
		RW++;
	}

	fclose(fin);
	printf("Total Read = %d\n",RW);
              

	//Initialize the page array.
	

	int it1=0;


	
		P=pageNumArr[1];
		initializePage();
		FIFO();	
				initializePage();
		CLOCK();	
				initializePage();
		LRU();	
	
	
	// for(it1=0;it1<2;it1++){
	// 	P=pageNumArr[it1];
	// 	initializePage();
	// 	FIFO();	
	// }

	// for(it1=0;it1<2;it1++){
	// 	P=pageNumArr[it1];
	// 	initializePage();
	// 	CLOCK();	
	// }

	// for(it1=0;it1<2;it1++){
	// 	P=pageNumArr[it1];
	// 	initializePage();
	// 	LRU();	
	// }
	

	return 0;
}