#include<stdio.h>
#include<string.h>


	

/*
   Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop.
   Assume a fixed set of tab stops, say every n columns.

*/

#define MAXLENGTH_LINE 100

#define TAB_SIZE 7 // equivalent to 7 spaces. Change tab sizes from 7 to 1 for testing.


int main(void){

	FILE *fp = fopen("t20.txt","r");
	char str[100];
	int line_max_len = MAXLENGTH_LINE;
	int len,i;
	char *p = NULL;
	char c;
	if(fp!=NULL){

		while(1){			
			len = getline_new(str,MAXLENGTH_LINE,fp);
			if(len == -1)
				break;
			if(len == 0 )
				continue;
			p = str;
			while((c=*p)){
				if(c == '\t')
					for(i=0;i<TAB_SIZE;i++)
						putchar(' ');
				else
					putchar(c);
				p++;
			}
			putchar('\n');
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
