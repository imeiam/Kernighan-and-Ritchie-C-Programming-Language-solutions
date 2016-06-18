/*
   Write a recursive version of the function reverse(s) , which reverses the string s in place.
   */

#include<stdio.h>
#include<string.h>

void rev(char s[], int first, int last) {
   	char tmp = s[first];
 	if (first >= last)
      		return;
	s[first] = s[last];
 	s[last] = tmp;
	rev(s, first + 1, last - 1);
}

int main(void){

	char str[100];
	puts("\nEnter the string: ");
	fgets(str,100,stdin);
	str[strlen(str)-1] = '\0'; // Avoid newline from fgets
	rev(str,0,strlen(str)-1);
	puts(str);
	return 0;
}
