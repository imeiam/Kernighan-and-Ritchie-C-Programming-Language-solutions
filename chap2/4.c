/*

	Write an alternate version of squeeze(s1,s2) that delete each character in s1 that matches any character in s2

	*/

#include<stdio.h>
#include<string.h>

void squeeze(char str1[], char str2[]);
void squeeze2(char str1[], char c);

int main(void){

	char str1[20],str2[20];
	fgets(str1,20,stdin);
	fgets(str2,20,stdin);
	squeeze(str1,str2);
	return 0;
}


void squeeze(char str1[], char str2[]){

	int len1 = strlen(str1);
	int len2 = strlen(str2);
	char ascii[128];
	memset(ascii,0,128);
	len1--;
	len2--;
	str1[len1] = '\0';
	str2[len2] = '\0';
	// find unique characters in str2 and delete them from str1
	//puts(str1);
	//puts(str2);
	//printf("\nLength: 1: %d 2: %d ",len1,len2);
	char *p = str2;
	while( *p ){
		
		if( ! ascii[*p] ){
			// value 0. Character occuring first time
			squeeze2(str1,*p);
			// delete characters from str1
			ascii[*p]++;
		}	
		p++;
	}
	printf("\nFormatted String: ");
	puts(str1);
}
void squeeze2(char s[], char c){
	int i,j;
	for(i=j=0;s[i]!='\0';i++)
		if(s[i]!=c)
			s[j++]=s[i];
	s[j] = '\0';
}
