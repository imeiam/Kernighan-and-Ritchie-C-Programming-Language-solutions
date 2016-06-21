/*
   Modify the pattern finding program of Chapter 5 to take its input
   from a set of named files or, if no files are named as arguments,
   from the standard input.

FORMAT:
	* ./a.out PATTERN FILE1 FILE2 .. FILE N

   Get aruguments.
   
   */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXFILES 10
#define MAXLEN 1000

#define USE_FILE 1
#define USE_STDIN 2

char *files[MAXFILES];
int file_count=0;
int type = USE_STDIN; // default


void find_pattern(char pattern[]){

	int count = 0;
	char teststr[MAXLEN];
	char *s;
	int pattern_len = strlen(pattern);
	if(type == USE_STDIN){
		puts("Enter the string to search: ");
		fgets(teststr,MAXLEN,stdin);
		teststr[strlen(teststr)-1] = '\0';
		s = teststr;
		while((s = strstr(s,pattern))!=NULL){
			// Everytime strstr find a pattern. Jump pattern_len locations to skip the pattern
			// so its not found again.
			s+=pattern_len;
			count++;	
		}
		printf("\nPattern occurred %d times in the given string\n",count);	
		
	} else {
		int i;
		FILE *fp;
		for(i=0;i<file_count;i++){
			fp = fopen(files[i],"r");
			if(fp!=NULL){
				while(fgets(teststr,MAXLEN,fp)!=NULL){
					teststr[strlen(teststr)-1] = '\0';
					s = teststr;
					while((s = strstr(s,pattern))!=NULL){
						s+=pattern_len;
						count++;
					}
				}
				if(count>0)
					printf("\nPattern Occurred %d times in File: %s",count,files[i]);
			}
			else{
				printf("Error: Cannot Open File: %s\n",files[i]);
				continue;
			}
			count=0;
		}
	}
	putchar('\n');
}

int main(int argc,char *argv[]){
	char pattern[MAXLEN];	
	int i;
	if(argc>1){
		strcpy(pattern,argv[1]);
		for(i=2;i<argc;i++){
			files[i-2] = (char *) malloc(strlen(argv[i]));
			strcpy(files[i-2],argv[i]);
		}
		if(i>2)
			type = USE_FILE;
		file_count = i-2;
	} else if(argc == 1){
		puts("Error: No pattern given");
		return 0;
	}
	find_pattern(pattern);
	return 0;
}
