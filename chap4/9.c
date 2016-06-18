/*
   Your getch and ungetch do not handle a pushed-back EOF correctly.
   Decide what their properties ought to be if an EOF is pushed back, then implement your design.

   */

#include<stdio.h>
#include<string.h>
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;


int getch(void){
	return (bufp > 0)? buf[--bufp] : getchar();
}

void ungetch(int c){
	if(bufp >= BUFSIZE)
		printf("\nUngetch: Too many characters");
	else
		buf[bufp++] = c;
}

void ungets(char *str){
	int i = strlen(str);
	while(i>0)
		ungetch(str[--i]);
}

int main(void){
	
	char p;
	while((p = getch())!= EOF){
		if(p == '$'){
			ungetch(EOF);
			continue;
		}
		putchar(p);
	}
	return 0;

}
