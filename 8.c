/*
   Write a function rightrot(x,n) that returns the value of the integer x rotated to the right by n bit positions.

*/

#include<stdio.h>

int rightrot(unsigned x,int n);

int main(void){
	int r;
	unsigned n;
	printf("\nEnter the number: ");	
	scanf("%u",&n);
	printf("\nEnter the number of bit rotations: ");	
	scanf("%d",&r);
	printf("\nValue: %u \n",rightrot(n,r));
	return 0;
}
int rightrot(unsigned x,int n){

	int i=0;
	n = n % 32; // size of unsigned - 32
	unsigned max_num = 0xFFFFFFFF;
	for(;i<n;i++){
		if( x & 1 ){
			x = x >> 1;
			x = x | ( max_num & ~( max_num  >> 1 )); // set the MSB.
		}
		else{
			x = x >> 1;
		}
	}
	return x;
}
