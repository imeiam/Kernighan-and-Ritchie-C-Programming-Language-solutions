/*
   Faster version of bit count
*/


#include<stdio.h>


int no_of_bits(int x){
	int count = 0;
	if(x>0){
		while((x= x & x-1)){
			count++;
		}
		count++; // for the last 1.
	}
	return count;
}

int main(void){
	int n;
	printf("\nEnter the number :");
	scanf("%d",&n);
	printf("\nCount: %d\n",no_of_bits(n));
	return 0;
}
