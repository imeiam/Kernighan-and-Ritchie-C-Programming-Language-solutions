/*
   Rewrite the function lower which converts upper case letter to lower case using condition expression
   */


#include<stdio.h>
int main(void){
	char str[20];
	puts("Enter the string:");
	fgets(str,20,stdin);
	char *p = str;
	char c = *p;
	while(*p){
		c = *p;
		*p = ( c>=65 && c<=91) ? c+32 : c ; 
		p++;
	}
	puts(str);
	return 0;
}
