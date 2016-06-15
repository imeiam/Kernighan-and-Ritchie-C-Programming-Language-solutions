#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LINES 10
#define MAX_LEN 1000
#define MAX_LINES 100

void sort(char *lines[],int n,int fold_flag){

	int i;
	char *p;

	if(fold_flag){
		for(i=0;i<n-1;i++){	
			if(strcasecmp(lines[i],lines[i+1])>0){
				p = lines[i];
				lines[i] = lines[i+1];
				lines[i+1] = p;
				i=-1;
			}
		}
	}
	else{
		for(i=0;i<n-1;i++){
			if(strcmp(lines[i],lines[i+1])>0){
				p = lines[i];
				lines[i] = lines[i+1];
				lines[i+1] = p;
				i=-1;
			}
		}
	}
}

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
	int flag;
	if(argc == 2){
		flag = (strcmp(argv[1],"-f")==0)? 1:0;
	}
	FILE *fp  = fopen("t15.txt","r");
	if(fp!=NULL){
		while((len = getlinex(line,MAX_LEN,fp)) != 0){
			lines[line_count] = (char *) malloc (MAX_LEN);
			strcpy(lines[line_count++],line);
			if(line_count == MAX_LINES)
				break;
		}
		int i;
		sort(lines,line_count,flag);
		puts("Results: ");
		for(i=0;i<line_count;i++)
			puts(lines[i]);
		fclose(fp);
	}
	return 0;
}
