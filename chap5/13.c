#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LINES 10
#define MAX_LEN 1000
#define MAX_LINES 100

int getlinex(char s[], int lim,FILE *fp)
{
	int c, i;
    	for (i = 0; i < lim - 1 && (c = fgetc(fp)) != EOF && c != '\n'; i++)
	 	s[i] = c;
	s[i] = '\0';
	return i;
}


int main(int argc,char *argv[]){
	char *lines[MAX_LINES];
	int len;
	char line[MAX_LEN];
	int line_count=0;
	if(argc != 2){
		fprintf(stderr,"Need arugments for tail.");
		return 0;
	}
	int arg = (argv[1][0] == '-')? (-1*atoi(argv[1])):-1;
	if(arg == -1 || arg == 0){
		fprintf(stderr,"Error in arugment");
		return 0;
	}
	FILE *fp  = fopen("t13.txt","r");
	if(fp!=NULL){
		while((len = getlinex(line,MAX_LEN,fp)) != 0){
			lines[line_count] = (char *) malloc ( len );
			strcpy(lines[line_count++],line);
			if(line_count == MAX_LINES)
				break;
		}
		int i;
		if(line_count-arg<0)
			i=0;
		else
			i = line_count - arg; // start index for last "tail" lines
		puts("Results: ");
		for(;i<line_count;i++)
			puts(lines[i]);
		fclose(fp);
	}
	return 0;
}
