/*

	Write an alternate version of squeeze(s1,s2) that delete each character in s1 that matches any character in s2

	*/

#include<stdio.h>
#include<string.h>
#include<limits.h>

int any(char s1[], char s2[]);

int main(void){

	char str1[20],str2[20];
	fgets(str1,20,stdin);
	fgets(str2,20,stdin);
	int code = any(str1,str2);
	if( code  == INT_MAX ){
		puts("Error not found");
	}
	else{
		printf("\nFound at: %d \n ",code);
	}
	return 0;
}


int any(char str1[], char str2[]){
	
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int flag=-1;
	char ascii[128];
	memset(ascii,0,128);
	len1--;
	len2--;
	str1[len1] = '\0';
	str2[len2] = '\0';
	char *p = str2;
	char *pos = NULL;
	int occ = INT_MAX;
	while( *p ){
		
		if( ! ascii[*p] ){
			// value 0. Character occuring first time
			if((pos = strchr(str1,*p))){
				if( (pos-str1) < occ )
					occ = pos - str1;
				// Check for the first occurance 
			}
			ascii[*p]++;
		}	
		p++;
	}
	return occ;
}
