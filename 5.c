/*
   Add access to library functions like sin , exp , and pow.
   */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define NUMBER 0
#define IDENTIFIER 1
#define MAXVAL 100
#define BUFSIZE 100

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
	int i, c, d,test=1;
	while((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';

	if(!isalnum(c) && c != '.' && c != '-')
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
	if(isalnum(c) || c == '-')
		while(isalnum(s[++i] = c = getch()));
	if(c == '.')
		while(isalnum(s[++i] = c = getch()));
	s[i] = '\0';
	if(c != EOF)
		ungetch(c);
	for(i=0;s[i] != '\0';i++)
		if(!isalpha(s[i])){
			test = 0;
			break;
		}
	if(test)
		return IDENTIFIER;
	else
		return NUMBER;
}



void display_top(void){
	if(sp > 0 ) 
		printf("\nTop of the stack: %lf\n",val[sp-1]);
	else
		printf("\nStack Empty\n");
}

void duplicate(void){

	if(sp>0){
		double top = pop();
		push(top);
		push(top);
	}
	else
		printf("\nStack Empty\n");
}

void swap_top_two(void){

	double one = pop();
	double two = pop();
	push(one);
	push(two);
}

// For this question


void identifier_handler(char s[]){

	if( strcmp(s,"sin") == 0){
		double top = pop();
		push(sin(top));
	
	} else if( strcmp(s,"cos") == 0){
		double top = pop();
		push(cos(top));
	} else if( strcmp(s,"pow") == 0){
		double base = pop();
		double exp = pop();
		push(pow(base,exp)); // Assuming pow(a,b) is b a pow in postfix
	}
}

int main()
{
	int type;
	double op2;
	char s[MAXOP];

	while((type = getop(s)) != EOF)
	{
		switch(type)
		{
			case NUMBER:
				push(atof(s));
				break;
			case IDENTIFIER:
				identifier_handler(s);
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
					printf("Error: zero divisor\n");
				break;
			case '%':
				op2 = pop();
				if(op2 != 0.0)
					push(fmod(pop(), op2));
				else
					printf("Error: division by zero\n");
				break;
			case '@':
				display_top();
				break;
			
			case '&':
				duplicate();
				break;

			case '#':
				swap_top_two();
				break;

			case '\n':
				if(sp>0)
					printf("\t%.8g\n", pop());
				break;
			default:
				printf("Error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}
