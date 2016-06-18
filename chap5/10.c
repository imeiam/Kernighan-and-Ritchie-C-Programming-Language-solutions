/*
   Write the program expr , which evaluates a reverse Polish expression from the command line, where each operator or operand is a separate argument. For example, 
   expr 2 3 4 + * 

Usage: ./a.out 12 12 + 
   */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>


#define MAXOP 100
#define NUMBER 0
#define MAXVAL 100
#define BUFSIZE 1000

int getop(char *);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void viewstack(void);

int bufp = 0;
char buf[BUFSIZE];
int sp = 0;
double val[MAXVAL];


void push(double f)
{
	if(sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
	if(sp > 0)
		return val[--sp];
	else
	{
		printf("error: stack empty\n");
		exit(1);
	}
}

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

int getop(char *s)
{
	int i, c, d;
	while((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';
	if(!isdigit(c) && c != '.' && c != '-')
		return c;
	if(c == '-')
	{
		d = getch();
		if(d == ' ')
			return c;
		else
			ungetch(d);
	}
	i = 0;
	if(isdigit(c) || c == '-')
		while(isdigit(s[++i] = c = getch()));
	if(c == '.')
		while(isdigit(s[++i] = c = getch()));
	s[i] = '\0';
	if(c != EOF)
		ungetch(c);
	return NUMBER;
}

void ungets(char *str){

	while(*str){
		ungetch(*str);
		str++;
	}
}

void rev(char str[],int len){
	int i=0,t;
	for(i=0;i<len/2;i++){
		t = str[i];
		str[i] = str[len-1-i];
		str[len-1-i] = t;
	}
}


int main(int argc,char *argv[])
{
	int type;
	double op2;
	char s[MAXOP];
	int i=0,j,k;
	char in[1000];
	for(i=1,j=0;i<argc;i++){
		in[j++] = ' ';
		for(k=0;argv[i][k]!='\0';k++)
			in[j++] = argv[i][k];
	}
	in[j++] = '\n';
	in[j] = '\0';
	rev(in,j);
	ungets(in);
	while((type = getop(s)) != EOF)
	{
		switch(type)
		{
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if(op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '%':
				op2 = pop();
				if(op2 != 0.0)
					push(fmod(pop(), op2));
				else
					printf("error: division by zero\n");
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}
