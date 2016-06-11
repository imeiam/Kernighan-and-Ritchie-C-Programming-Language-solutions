/*
   Write a function itob(n,s,b) that converts the integer n into a base b character representation in the string s.
   In particular, itob(n,s,16) formats n as a hexadecimal integer in s.
   */

#include<string.h>
#include<stdio.h>
void reverse(char str[]){
	
	int len = strlen(str),i,j;
	char c;
	for(i=0,j = len -1;i<j;i++,j--){
		c = str[i];
		str[i] = str[j];
		str[j] = c;
	}
}

void itoa(int n,char str[],int b){

	int i,sign,t;
	sign = n;
	i=0;
	do{
		t = abs(n%b);
		if(t<10)
			str[i++] = t + '0';
		else
			str[i++] = t - 10 + 'A';
	}while(n/=b); 
	if(sign<0)
		str[i++] = '-';
	str[i] = '\0';
	reverse(str);
}

int main(void){
	char str[100];
	int n,b;
	puts("\nEnter the number: ");
	scanf("%d",&n);
	
	puts("\nEnter the base: ");
	scanf("%d",&b);

	itoa(n,str,b);
	puts("\nFinal String: ");
	puts(str);
	return 0;
}
