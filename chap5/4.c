/*
Write the function strend(s,t) , which returns 1 if the string t occurs at the end of the string s , and zero otherwise.
*/

#include<stdio.h>
#include<string.h>


int strendx(char s[], char t[]){
	
	char *sp = s+ strlen(s);
	char *tp = t+ strlen(t);
	if(sp-s<tp-t) return 0;
	while( *--sp == *--tp ){
		if(tp == t)
			return 1;
	}
	return 0;
}

int main(void){
	
	char str1[100],str2[100];
	puts("Enter the two string: ");
	fgets(str1,100,stdin);
	fgets(str2,100,stdin);
	str1[strlen(str1)-1]='\0';
	str2[strlen(str2)-1]='\0';
	if(strendx(str1,str2))
		puts("String 2 occurs at end of String 1");
	else
		puts("String 2 does not occur at end of String 1");
	return 0;
}
