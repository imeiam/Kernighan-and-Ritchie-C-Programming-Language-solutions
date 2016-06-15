/*
   Write a getFloat function similar to getInt
   */

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
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

int getfloat(float *pn){

	int c,sign,sign_flag=0;
	error_flag = 0;
	int fraction_flag = 0;
	int exp_count = 0;

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
			return 0;
		}
	}
	for ( *pn = 0; isdigit(c) || c=='.';c = getch()){
		if(c == '.'){
			fraction_flag = 1;
			continue;
		}
		*pn = 10 * (*pn) + ( c - '0' );
		if(fraction_flag)
			exp_count++;
	}
	*pn = *pn * ( sign/pow(10.0,exp_count));
	if(c!=EOF)
		ungetch(c);
	return c;

}

int main(void){
	
	float a;
	getfloat(&a);
	if(!error_flag)
		printf("\nResult: %.3lf \n",a);
	else{
	// error
		printf("\nError, Character pushed back: %c \n",buf[0]);
	}
	return 0;

}
