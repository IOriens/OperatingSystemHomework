#include <stdio.h>
#define INF 10000
void insertionSort(int *arr,int n);
int main(){
	printf("Please input n:");
	int n=0;
	scanf("%d",&n);
	int arr[INF]={0};
	int i=0;
	for(i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	insertionSort(arr,n);
	for(i=0;i<n;i++){
		printf("%d\n",arr[i]);
	}
	return 0;
}
void insertionSort(int *arr,int n){
	int l=0,j=0,r=0;
	for(j=1;j<n;j++){
		l=0;
		r=j-1;
		int key=arr[j];
		if(key<arr[0]){
			l=0;
		}else if(key > arr[r]){
			l=r+1;
		}else{
			int mid =(l+r)/2;
			while(r-l>0){
				int m=arr[mid];
				if(key==m){
					l=mid;
					break;
				}else if(r-l==1){
					l=r;
					break;	
				}else if(key>m){
					l=mid;
				}else{
					r=mid;
				}	
			}
		}
		int i2=0;
		for(i2=j;i2>l;i2--){
			arr[i2]=arr[i2-1];
		}
		arr[l]=key;
	/*	while(i>=0 && arr[i]>key){
			int temp=arr[i+1];
			arr[i+1]=arr[i];
			arr[i]=temp;
			i--;
		}
		arr[i+1]=key;*/
	}
}
