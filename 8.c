/*
   Write a routine ungets(s) that will push back an entire string onto the input.
   Should ungets know about buf and bufp , or should it just use ungetch ?

   */

#include<stdio.h>
#include<string.h>
#define BUFSIZE 100

int buf = EOF;

int getch(void){
	char t;
	if(buf == EOF)
		t = getchar();
	else{
		t = buf;
		buf = EOF;
	}
	return t;
}

void ungetch(int c){
	if(buf!=EOF)
		printf("\nUngetch: Too many characters");
	else
		buf = c;
}
int main(void){
	
	char p;
	while((p = getch())!= EOF){
		if(p == '#'){
			ungetch('&');
		}
		else
			putchar(p);
	}
	return 0;

}
