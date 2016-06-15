/*
   Add -r flag to sort program.
   */

#include<stdio.h>

#define MAX_LEN 100

void sort(int arr[],int n,int rev_flag){

	int i,j;
	if(rev_flag){
		for(i=0;i<n-1;i++){
	
			if(arr[i]<arr[i+1]){
				j = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = j;
				i=-1;
			}
		}
	}
	else{
		for(i=0;i<n-1;i++){
			if(arr[i]>arr[i+1]){
				j = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = j;
				i=-1;
			}
		}
	}
}


int main(int argc,char *argv[]){
	
	int n;
	int flag=0;
	if(argc==2){
		flag = (strcmp(argv[1],"-r")==0)? 1:0;
	}
	puts("\nEnter number of items to sort: ");
	scanf("%d",&n);
	if(n>MAX_LEN){
		fprintf(stderr,"Size overflow. Try a smaller number\n");
		return 0;
	}
	puts("\nEnter the items:");
	int i;
	int arr[MAX_LEN];
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	sort(arr,n,flag);
	puts("\nResults: ");
	for(i=0;i<n;i++)
		printf("%d\n",arr[i]);
	return 0;
}
