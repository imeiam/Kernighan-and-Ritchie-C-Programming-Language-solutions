/*
   Write a pointer version of the function strcat that we showed in Chapter 2: strcat(s,t) copies the string t to the end of s
   */

#include<stdio.h>
#include<string.h>


void strcatx(char s[], char t[]){
	
	char *sp = s+ strlen(s);
	char *tp = t;
	while(( *sp++ = *t++ )!='\0');
}

int main(void){
	
	char str1[100],str2[100];
	puts("Enter the two string: ");
	fgets(str1,100,stdin);
	fgets(str2,100,stdin);
	str1[strlen(str1)-1]='\0';
	str2[strlen(str2)-1]='\0';
	strcatx(str1,str2);
	puts(str1);
	return 0;
}
