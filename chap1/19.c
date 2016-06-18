#include<stdio.h>
#include<string.h>

/*
	Write a function reverse(s) that reverses the character string s . Use it to write a program that reverses its input a line at a time.

*/

#define MAXLENGTH_LINE 100


int main(void){

	FILE *fp = fopen("t19.txt","r");
	char str[100];
	int line_max_len = MAXLENGTH_LINE;
	int len,i;
	char c;
	if(fp!=NULL){

		while(1){			
			len = getline_new(str,MAXLENGTH_LINE,fp);
			if(len == -1)
				break;
			if(len == 0 )
				continue;
			// String reverse logic
			for(i=0;i<len/2;i++){
				c = str[i];
				str[i]= str[len-1-i];
				str[len-1-i] = c;
			}	
			puts(str);
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
