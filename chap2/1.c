/*
   Write a program to determine the ranges of char , short , int , and 
   long variables, both signed and unsigned , by printing appropriate values from standard headers and by direct computation.
   */

#include<stdio.h>
#include<limits.h>

int main(void){


	// Using limit.h


	printf("Using limits.h");
	// char
	printf("\nChar:");
	printf("\nSigned: Max: %d Min: %d \n",SCHAR_MAX,SCHAR_MIN);
	printf("\nUnsigned: Max: %d\n",UCHAR_MAX);



	// short
	printf("\nShort:");
	printf("\nSigned: Max: %d Min: %d \n",SHRT_MAX,SHRT_MIN);
	printf("\nUnsigned: Max: %d\n",USHRT_MAX);

	// int
	printf("\nInt:");
	printf("\nSigned: Max: %d Min: %d \n",INT_MAX,INT_MIN);
	printf("\nUnsigned: Max: %u\n",UINT_MAX);

	// long
	printf("\nLong:");
	printf("\nSigned: Max: %ld Min: %ld \n",LONG_MAX,LONG_MIN);
	printf("\nUnsigned: Max: %lu\n",ULONG_MAX);

	printf("\nCalculated");


	unsigned char c;
	c = ~0;
	c>>=1;

	// char
	printf("\nChar:");
	printf("\nSigned: Max: %d Min: %d \n",c,-c-1);
	printf("\nUnsigned: Max: %d\n",2*c+1);

	unsigned short s;	
	s = ~0;
	s>>=1;
	// short
	printf("\nShort:");
	printf("\nSigned: Max: %d Min: %d \n",s,-s-1);
	printf("\nUnsigned: Max: %d\n",s*2+1);

	unsigned int i;
	i = ~0;
	i>>=1;
	// int
	printf("\nInt:");
	printf("\nSigned: Max: %d Min: %d \n",i,-1-i);
	printf("\nUnsigned: Max: %u\n",2*i+1);

	unsigned long l;
	l = ~0;
	l>>=1;
	// long
	printf("\nLong:");
	printf("\nSigned: Max: %ld Min: %ld \n",l,-1-l);
	printf("\nUnsigned: Max: %lu\n",2*l+1);
	return 0;
}
