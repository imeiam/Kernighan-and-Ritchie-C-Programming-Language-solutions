/*
   Write the function strrindex(s,t) , which returns the position of 
   the rightmost occurrence of t in s , or -1 if there is none.
   */

#include<stdio.h>
#include<string.h>

int strrindex(char str[],char t){
	
	if(strlen(str)>0){
		int i;
		for(i=strlen(str)-1;i>=0;i--){
			if(str[i] == t)
				return i;
		}
	}
	return -1;
}

int main(void){
	char str[100],t;
	puts("\nEnter the string: ");
	fgets(str,100,stdin);
	int len = strlen(str);
	len--;
	str[len] = '\0'; // Avoid newline from fgets.
	puts("\nEnter the character to search: ");
	t = getchar();
	//printf("\nString: %s Character: %c",str,t);
	printf("\nResult: %d\n",strrindex(str,t));
	return 0;
}
