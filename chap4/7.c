/*
   Write a routine ungets(s) that will push back an entire string onto the input.
   Should ungets know about buf and bufp , or should it just use ungetch ?

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
	
	char *str = "Hello This is Sonny";
	ungets(str);
	char p;
	while((p = getch())!= EOF)
		putchar(p);
	return 0;

}
