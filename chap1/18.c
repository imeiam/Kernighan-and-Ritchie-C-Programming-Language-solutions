#include<stdio.h>
#include<string.h>

/*

Write a program to remove all trailing blanks and tabs from each line of input, and to delete entirely blank lines.

*/


#define MAXLENGTH_LINE 100


int main(void){

	FILE *fp = fopen("t18.txt","r");
	char str[100];
	int line_max_len = MAXLENGTH_LINE;
	int len;
	char *p = NULL;
	char c;
	if(fp!=NULL){

		while(1){			
			len = getline_new(str,MAXLENGTH_LINE,fp);
			if(len == -1)
				break;
			if(len == 0 )
				continue;
			p = str + len - 1;
			while(p != str){
				c = *p;
				if( c == ' ' || c == '\t')
					*p = '\0';
				else
					break;
				p--;
			}
			len = (int) strlen(str);	
			if(len == 1 && ( *str == ' ' || *str == '\t' ))
				continue;	
			puts(str);
			//printf("Length: %d\n",len); Use this to test.
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
