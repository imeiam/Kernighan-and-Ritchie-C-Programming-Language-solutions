#include<stdio.h>
#include<string.h>

/*
   Write a program to check a C program for rudimentary syntax errors like unbalanced parentheses, brackets and braces.
   Don't forget about quotes, both single and double, escape sequences, and comments.
   (This program is hard if you do it in full generality)

*/

#define MAXLENGTH_LINE 3000

#define NOT_COMMENT 0
#define STAR_COMMENT 1
#define INSIDE_SQUOTE 2 //SINGLE QUOTE
#define INSIDE_DQUOTE 3 //DOUBLE QUOTE

int getline_new(char line[],int lim,FILE *fp);

int main(void){

	FILE *fp = fopen("t24.txt","r");
	char str[MAXLENGTH_LINE],new_str[MAXLENGTH_LINE];
	int line_max_len = MAXLENGTH_LINE;
	int len,i,j;
	char c;
	char *p = NULL;
	int new_index=0;
	int state = NOT_COMMENT;
	int flag_single_line_comment = 1;
	int parentheses,braces,brackets;
	parentheses = braces = brackets  = 0;

	if(fp!=NULL){

		while(1){			
			len = getline_new(str,MAXLENGTH_LINE,fp);
			if(len == -1)
				break;
			if(len == 0)
				continue;
			p = str;
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
							switch(c){
								case '{':
									braces++;
									break;
								case '}':
									braces--;
									break;
								case '(':
									parentheses++;
									break;
								case ')':
									parentheses--;
									break;
								case '[':
									brackets++;
									break;
								case ']':
									brackets--;
									break;

							}
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

		if(braces != 0){
			printf("\n Error: Unmatched braces!\n");

		}
		if ( parentheses != 0 ){
			printf("\n Error: Unmatched parentheses!\n");
		} 
		if ( brackets != 0){
			printf("\n Error: Unmatched brackets!\n");
		}
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

