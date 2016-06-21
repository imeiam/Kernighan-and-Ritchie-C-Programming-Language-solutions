/*
   Write a program to compare two files, printing the first line where they differ.
   */

#include<stdio.h>






int cmpfiles(FILE *sp, FILE *tp){

	int lineno=1;
	
	char s,t;

	while(1){

		s = fgetc(sp);
		t = fgetc(tp);
	
		if(s!=t)
			return lineno;
		if(s=='\n')
			lineno++;
		if(s==EOF)
			break;
	}
	return 0;
}




int main(void){

	int result=0;

	FILE *sp = fopen("t6.txt","r");
	FILE *tp = fopen("t6b.txt","r");

	if( sp == NULL || tp == NULL ){
		puts("Error in reading the file");
		return 0;
	}

	if(!(result=cmpfiles(sp,tp)))
		puts("Two files are identically");
	else
		printf("Files differ at line no: %d \n",result);
	return 0;
}
