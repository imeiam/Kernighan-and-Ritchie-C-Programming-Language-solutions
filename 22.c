#include<stdio.h>
#include<string.h>

/*

   Write a program to "fold" long input lines into two or more shorter lines after the last non-blank character that occurs before the n-th column of input. 
   Make sure your program does something intelligent with very long lines, and if there are no blanks or tabs before the specified column.

*/

#define MAXLENGTH_LINE 3000

#define FOLD_SIZE 150


int getline_new(char line[],int lim,FILE *fp);

int main(void){

	FILE *fp = fopen("t22.txt","r");
	char str[MAXLENGTH_LINE],new_str[MAXLENGTH_LINE];
	int line_max_len = MAXLENGTH_LINE;
	int len,i,j;
	char c;
	int new_index=0,space_index = -1,counter=0,start=0;
	if(fp!=NULL){

		while(1){			
			len = getline_new(str,MAXLENGTH_LINE,fp);
			if(len == -1)
				break;
			if(len == 0)
				continue;
			if(len <= FOLD_SIZE){
				puts(str);
				continue;
			}
			start=0;
			counter=0;
			for(i=0;i<strlen(str);i++){

				c = str[i];
				counter++;

				if(c == ' '){
					space_index = i;		
				}
				
				if( counter == FOLD_SIZE ){
					
					if(space_index == -1){


						for(j=start;j<i;j++){
							new_str[new_index++] = str[j];
						}
						new_str[new_index++] = '-';
						new_str[new_index++] = '\n';
						new_str[new_index++] = str[i];
						counter = 1; // one character in next line is entered already.  akil -> aki-\nl
						start = i+1;
					} else {

						for(j=start;j<space_index;j++){
							new_str[new_index++] = str[j];
						}
						new_str[new_index++] = '\n';
						start = space_index + 1;
						counter = i - start + 1;
						space_index=-1;
					}
				}
			}
			new_str[new_index] = '\0';
			puts(new_str);
			new_index = 0; // reset for next line
		}
		fclose(fp);
	}
	return 0;
}
int getline_new(char line[],int lim,FILE *fp){

	int c,i;
	for(i=0;i<lim-1 && (c=fgetc(fp))!=EOF && c!='\n';i++)
		line[i] = c;
	line[i] = '\0';
	if(c == EOF)
		return -1;
	else
		return i;
}

