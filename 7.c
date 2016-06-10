/*
   Write a function invert(x,p,n) that returns x with the n bits that begin at position p set ot the rightmost n bits of y, leaving the other bits unchanged.
   */

#include<stdio.h>
#include<math.h>

unsigned invertbits(unsigned x, int p, int n);
unsigned setbits(unsigned x, int p, int n, int y);
int powerx(int x,int y);
int main(void){
	//printf("%d\n",setbits(41,3,3,91));
	printf("%d\n",invertbits(87,5,3));
	return 0;
}
unsigned invertbits(unsigned x, int p, int n){
	return x ^ ((powerx(2,n) - 1) << (p+1-n));
}

int powerx(int x,int y){

	int prod = 1,i;
	for(i=0;i<y;i++){
		prod*=x;
	}
	return prod;
}
