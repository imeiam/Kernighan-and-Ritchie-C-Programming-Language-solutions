/*
   Write a program that converts upper case to lower or lower case to upper, 
   depending on the name it is invoked with, as found in argv[0].

   */


#include<stdio.h>


#define UPPER 1
#define LOWER 2
#define DEFAULT LOWER

#define MAXLEN 200
#define BUFSIZE 1000

char buf[BUFSIZE];
int bufp = 0;
int getch(FILE *fp);
void ungetch(int c);
int getlinex(char *str,int lim,FILE *fp);




int getch(FILE *fp){
	return (bufp > 0)? buf[--bufp] : fgetc(fp);
}

void ungetch(int c){
	if(bufp >= BUFSIZE)
		printf("\nUngetch: Too many characters");
	else
		buf[bufp++] = c;
}

int getlinex(char *str,int lim,FILE *fp){

	char *p = str,c;
	while(--lim>0 && (c = fgetc(fp)) && c!=EOF && c!='\n')
		*p++ = c;
	if(c=='\n')
		*p++ = c;
	*p = '\0';
	return p-str;
}



int type = DEFAULT;

int main(int argc,char *argv[]){
	if(argc>1){
		if(strcmp(argv[1],"tolower")==0){
			type = LOWER;
		}
		else if( strcmp(argv[1],"toupper") ==0){
			type = UPPER;
		}
	}
	puts("\nEnter the words:");
	char line[MAXLEN];
	char *p;
	while(getlinex(line,MAXLEN,stdin)>0){
		p = line;
		while(*p){
			if(type==LOWER){
				putchar(tolower(*p));
			}
			else
				putchar(toupper(*p));
			p++;
		}
	}
	return 0;
}
