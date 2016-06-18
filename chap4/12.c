/*
   Adapt the ideas of printd to write a recursive version of itoa ; that is, convert an integer into a string by calling a recursive routine

   */

#include<stdio.h>


static char char_set[] = "0123456789abcdefghijklmnopqrstuvwxyz";

char *itoa(int n, char str[], int base)
{
	int mod = n % base;
	int n_new = n / base;	      
	if (n_new < 0) {	
		*str++ = '-';
		mod = -mod;
		n_new = -n_new;
	}
	if (n_new)
		str = itoa(n_new, str, base);
	*str++ = char_set[mod];
	*str = '\0';
	return str;
}

int main(void){
	char str[100];
	int n;
	puts("\nEnter the number: ");
	scanf("%d",&n);
	char *p = itoa(n,str,2);
	puts(str);
	return 0;
}
