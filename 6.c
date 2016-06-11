/*
   Write a version of itoa that accepts three arguments instead of two.
   The third argument is a minimum field width; the converted number must be padded with blanks on the left if necessary to make it wide enough.
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

void itoa(int n,char str[],int b,int width){

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
	int len = strlen(str);
	reverse(str);
	if(width>len){
		int space = width - len;
		for(i=len;i>=0;i--) // Including null
			str[i+space] = str[i];
		for(i=0;i<space;i++)
			str[i] = '*'; // Space. Star used for clearer display
	}
	puts("\nFinal String: ");
	puts(str);
}

int main(void){
	char str[100];
	int n,b,width;
	puts("\nEnter the number: ");
	scanf("%d",&n);
	
	puts("\nEnter the base: ");
	scanf("%d",&b);

	puts("\nEnter the width");
	scanf("%d",&width);

	itoa(n,str,b,width);
	return 0;
}
