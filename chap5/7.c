/*
   Rewrite readlines to store lines in an array supplied by main , rather than calling alloc to maintain storage.
*/


#include<stdio.h>


#define MAXLEN 1000
#define MAXLINES 10


char lines[MAXLINES][MAXLEN];

int getlinex(char s[], int lim)
{
	int c, i;
    	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		s[i] = c;
	s[i] = '\0';
	return i;
}

int readlines(char lines[][MAXLEN],int maxlines){
	
	int line_count = 0;
	char line[MAXLEN];
	int len;
	while((len = getlinex(lines[line_count],MAXLEN))>0){
		if(line_count>=maxlines)
			return -1;
		else
			line_count++;
	}
	return line_count;
}

int main(void){
	
	int line_count = readlines(lines,MAXLEN);
	puts("Results:");
	int i;
	for(i=0;i<line_count;i++)
		puts(lines[i]);
	return 0;
}
