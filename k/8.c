/*
   Write a program to print a set of files, starting each new one on a new page, with
   a title and a running page count for each file.

FORMAT - ./a.out FILE1 FILE2 .. FILE N
   */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXLEN 500


#define LINES_IN_PAGE 8


void print_file(char file[]){
	FILE *fp = fopen(file,"r");
	int page_no= 0;
	int line_count= LINES_IN_PAGE;
	if(fp==NULL)
		printf("Error: Cannot open file: %s\n",file);
	else{
		char c;
		printf("\n\nFile: %s\n",file);
		int i;
		for(i=0;i<(6+strlen(file));i++)
			printf("=");
		puts("\n\n");
		while((c= fgetc(fp))!=EOF){
			if(line_count == LINES_IN_PAGE){
				if(page_no!=0)
					printf("\n\nPage %d File :%s ends\n\n",page_no,file);
				printf("\n\nPage %d File :%s begins\n\n",++page_no,file);
				line_count = 0;
			}
			if(c=='\n')
				line_count++;
			putchar(c);
		}		
		printf("\n\nPage %d File :%s ends\n\n",page_no,file);
	}
}


int main(int argc,char *argv[]){
	int i;
	if(argc>1)
		for(i=1;i<argc;i++)
			print_file(argv[i]);
	else if(argc == 1)
		puts("Error: No Files found");
	return 0;
}
