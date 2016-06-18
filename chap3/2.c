/*
   Write a function escape(s,t) that converts characters like newline and tab into visible escape sequences like \n and \t as it copies the string t to s. Use Switch. Write a function for the other direction as well.

   */


// I have read data from a file t2.txt and completed the above conversions.

#include<stdio.h>

int main(void){
	// Escape to real characters
	FILE *fp = fopen("t2.txt","r");	
	char c,t;
	if(fp!=NULL){
		while((c = fgetc(fp))!=EOF){
			switch(c){
				case '\n':
					putchar('\\');
					putchar('n');
					break;
				case '\t':
					putchar('\\');
					putchar('t');
					break;
				default:
					putchar(c);
			}
		}
		fclose(fp);
	}
	putchar('\n');
	// Real characters to escape sequences.
	fp = fopen("t2b.txt","r");	
	if(fp!=NULL){
		while((c = fgetc(fp))!=EOF){
			switch(c){
				case '\\':
					t = fgetc(fp);
					switch(t){
						case 't':
							putchar('\t');
							break;
						case 'n':
							putchar('\n');
							break;
						case '\\':
							putchar('\\');
							fseek(fp,-1,SEEK_CUR);
							continue;
						default:
							putchar('\\');
					}
					if(t == EOF )
						return 0;
					break;
				default:
					putchar(c);
			}
		}
		fclose(fp);
	}
	return 0;
}
