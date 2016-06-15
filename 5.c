/*
   Write versions of the library functions strncpy , strncat , and strncmp , which operate on at most the first n characters of their argument strings. For example, strncpy(s,t,n) copies at most n characters of t to s . Full descriptions are in Appendix B.
*/

#include<stdio.h>
#include<string.h>

int min(a,b){ return (a>b)? b:a;}


void strncpyx(char s[], char t[],int n){
	
	int lens = strlen(s);
	int lent = strlen(t);
	int limit = (lent > n)? n: lent;
	int i,j;
	for(i=0,j=0;j<limit;j++,i++)
		s[i] = t[j];
	s[i] = '\0';
}


void strncatx(char s[], char t[],int n){
	
	int lens = strlen(s);
	int lent = strlen(t);
	int limit = (lent > n)? n: lent;
	int i,j;
	for(i=lens,j=0;j<limit;j++,i++)
		s[i] = t[j];
	s[i] = '\0';
}


int strncmpx(char s[], char t[],int n){
	
	int lens = strlen(s);
	int lent = strlen(t);
	int limit = min(min(lens,n) ,lent );
	int i;
	for(i=0;i<limit;i++){
		if(s[i]!=t[i])
			return s[i] - t[i];
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
	puts("Enter the value of n: ");
	int n;	
	scanf("%d",&n);
	/*
	puts("\nCopy: ");
	strncpyx(str1,str2,n);
	puts(str1);

	puts("\nConcat: ");
	strncatx(str1,str2,n);
	puts(str1);
	*/
	if(!strncmpx(str1,str2,n))
		puts("Same");
	else
		puts("Different");

	return 0;
}
