/*
   As written, getint treats a + or - not followed by a digit as a valid representation of zero. Fix it to push such a character back on the input
   */

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define BUFSIZE 100

static int error_flag = 0;

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

int getint(int *pn){

	int c,sign,sign_flag=0;
	error_flag = 0;

	while(isspace(c = getch()));

	if(!isdigit(c) && c!=EOF && c !='+' && c!='-'){
		ungetch(c);
		return 0;
	}
	sign  = ( c == '-' )? -1:1;
	if(c=='+' || c == '-')
		sign_flag=1;
	if(sign_flag){
		char t = getch();
		if(isdigit(t))
			c = t;
		else{
			ungetch(c);
			ungetch(t);
			error_flag = 1;
			printf("\nval : %d",bufp);
			return 0;
		}
	}
	for ( *pn = 0; isdigit(c);c = getch())
		*pn = 10 * (*pn) + ( c - '0' );
	*pn = *pn * sign;
	if(c!=EOF)
		ungetch(c);
	return c;

}

int main(void){
	
	int a;
	getint(&a);
	if(!error_flag)
		printf("\nResult: %d \n",a);
	else{
	// error
		printf("\nError, Character pushed back: %c \n",buf[0]);
	}
	return 0;

}
