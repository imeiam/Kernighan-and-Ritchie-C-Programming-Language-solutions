#include<stdio.h>
#include<string.h>

/*
   Write a program to remove all comments from a C program. Don't forget to handle quoted strings and character constants properly.
   C comments do not nest.

Assumptions: Given C program is valid.

*/

#define MAXLENGTH_LINE 3000

#define NOT_COMMENT 0
#define STAR_COMMENT 1
#define INSIDE_SQUOTE 2 //SINGLE QUOTE
#define INSIDE_DQUOTE 3 //DOUBLE QUOTE

int getline_new(char line[],int lim,FILE *fp);

int main(void){

	FILE *fp = fopen("t23.txt","r");
	char str[MAXLENGTH_LINE],new_str[MAXLENGTH_LINE];
	int line_max_len = MAXLENGTH_LINE;
	int len,i,j;
	char c;
	char *p = NULL;
	int new_index=0;
	int state = NOT_COMMENT;
	int flag_single_line_comment = 1;
	if(fp!=NULL){

		while(1){			
			len = getline_new(str,MAXLENGTH_LINE,fp);
			if(len == -1)
				break;
			if(len == 0)
				continue;
			p = str;
//			puts(str);
			flag_single_line_comment = 1;
			while(*p && flag_single_line_comment){
				c = *p;
				switch(state){

					case NOT_COMMENT:
						 if( c == '/' && (*(p+1)) == '*' ){
							state = STAR_COMMENT;
							p+=2;
							
						 } else if( c == '/' && (*(p+1)) == '/' ){
							flag_single_line_comment = 0;
							break; // No need to scan the line anymore.
						} else if( c == '"' ){
							state = INSIDE_DQUOTE;
							new_str[new_index++] = '\"'; 
							p++;

						} else if( c == '\'') {
							state = INSIDE_SQUOTE;
							new_str[new_index++] = '\''; 
							p++;
						} else { 
							new_str[new_index++] = c; 
							p++;
							// No change in state;
						}
						break;

					case STAR_COMMENT:
						if( c == '*' && (*(p+1)) == '/' ){
							state = NOT_COMMENT;
							p+=2;
						}
						else{
							p++; // Skip
						}
						break;

					case INSIDE_SQUOTE:
						if( c == '\''){
							state = NOT_COMMENT;	
						}
						new_str[new_index++] = c; 					
						p++; // either case increment pointer
						break;

					case INSIDE_DQUOTE:
						if( c == '\"'){
							state = NOT_COMMENT;
						}
						new_str[new_index++] = c;
						p++; // either case increment pointer
						break;
				}
			}
			new_str[new_index] = '\0';
			// Print if not empty
			if(new_index != 0)
				puts(new_str); 
			new_index = 0;
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

