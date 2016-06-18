/*
   Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p set to the righmost n bits of y, leaving the other bits unchanged.

   */

#include<stdio.h>


unsigned setbits(unsigned x, int p, int n, int y);

int main(void){
	//printf("%d\n",setbits(41,3,3,91));
	printf("%d\n",setbits(15,3,3,0));
	return 0;
}
unsigned setbits(unsigned x, int p, int n, int y){
	
	return ( y & (~0 << n) ) | ( x >> (p+1-n) ) & ~ ( ~0 << n ); // clear last n bits of y, take n bits of x from position p and or the result.
}
