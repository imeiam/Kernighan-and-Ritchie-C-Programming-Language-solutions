/*
   In a two's complement number representation, our version of itoa does not handle the largest negative number, 
   that is, the value of n equal to -(2 to the power (wordsize - 1)).
   Explain why not. Modify it to print that value correctly regardless of the machine on which it runs.

   */

#include<stdio.h>
#include<string.h>


/*
   Problem with old method: stmt: sign = n; n = -n; when n is negative in
   method, we cannot represent -128 or the largest negative number for a 
   given word size, as there is no positive equivalent( +128 ) for the 
   given word size. 
   */


void reverse(char str[]){
	
	int len = strlen(str),i,j;
	char c;
	for(i=0,j = len -1;i<j;i++,j--){
		c = str[i];
		str[i] = str[j];
		str[j] = c;
	}
}

void itoa(int n,char str[]){

	int i,sign;
	sign = n;
	i=0;
	do{
		str[i++] = abs(n%10) + '0'; // using absolute for negative numbers
	}while(n/=10); // to work with for negative numbers.
	if(sign<0)
		str[i++] = '-';
	str[i] = '\0';
	reverse(str);
}

int main(void){
	char str[100];
	int n;
	puts("\nEnter the number: ");
	scanf("%d",&n);
	itoa(n,str);
	puts("\nFinal String: ");
	puts(str);
	return 0;
}
