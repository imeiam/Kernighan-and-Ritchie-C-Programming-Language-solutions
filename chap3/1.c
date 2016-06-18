#include<stdio.h>

int binsearch(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n-1;	        
	while(low < high) {
		mid = (low+high)/2;
		if(x <= v[mid]) 
			high=mid;
		else 
			low = mid+1;
	}	  
	return (x == v[low])?low : -1;
}


int main(void){


	int arr[] = {1,4,6,7,8,11,13,15,16,46,57,68,69};
	int search = 12;
	printf("Result: %d at %d ",search,binsearch(search,arr,sizeof(arr)/sizeof(arr[0])));
	return 0;
}
