/*

   */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP 100
#define NUMBER 1
#define IDENTIFIER 2
#define MAXVAL 100
#define BUFSIZE 100


#define NO_OF_VAR 32
#define VAR_USING 230
#define VAR_DECLARING 231


#define MAXLINE 100


char line[MAXLINE];
int line_index;


typedef struct x{
	char name[30];
	double val;
}variable;

variable last_used;
variable all_var[NO_OF_VAR];
int var_count = 0;
int var_state = VAR_USING;


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

int getlinex(char s[], int lim)
{
	int c, i;
	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if(c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

void clear_stack(void){
	// Clear stack 
	sp = 0;
	// Reset variable list.
	int i=0;
	for(;i<var_count;i++){
		all_var[i].name[0] = '\0';
		all_var[i].val = 0.0;
	}
	var_count = 0;
}

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
	while((s[0] = c = line[line_index++]) == ' ' || c == '\t');
	s[1] = '\0';

	if(!isalnum(c) && c != '.' && c != '-')
		return c;
	if( s[0] == '=' ){
		return s[0];
	}
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
		while(isalnum(s[++i] = c = line[line_index++]));
	if(c == '.')
		while(isalnum(s[++i] = c = line[line_index++]));
	s[i] = '\0';
	if(c != '\0')
		line_index--;
	for(i=0;s[i] != '\0';i++)
		if(!isalpha(s[i])){
			test = 0;
			break;
		}
	// Assumption: Variable contains only alphabets.
	if(test)
		return IDENTIFIER;
	else{
		return NUMBER;
	}
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
	} else {
		// Variable

		if(var_state == VAR_USING){
			
			int i=0,var_present=0;
			for(;i<var_count;i++)
				if(strcmp(s,all_var[i].name) == 0){
					push(all_var[i].val);
					var_present=1;	
					break;
				}
			if(!var_present){

				printf("\nError: Variable not declared");
				clear_stack();
			}

		}
		else{
			int i=0,unique_flag=1;
			for(;i<var_count;i++){
				if(strcmp(s,all_var[i].name) == 0){
					unique_flag = 0; // Already declared variable
					all_var[i].val = pop();
					last_used = all_var[i]; // update last used
					break;
				}
			}
			if(unique_flag){
				// New variable
				strcpy(all_var[var_count].name,s);
				all_var[var_count].val = pop();
				last_used = all_var[var_count]; // update last used
				var_count++;
			}
			var_state = VAR_USING; // Change to default state after declaring the variable
		}
	}
}

int main()
{
	int type;
	double op2;
	char s[MAXOP];

	while((getlinex(line,MAXLINE) != 0 )){
		line_index=0;
		
		while((type = getop(s)) != '\0')
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
	
				case '=':
					var_state = VAR_DECLARING; // used by identifier handler
					break;
	
				case '>':
					if(var_count > 0){
						printf("\nUsing Variable: %s with value %g\n",last_used.name,last_used.val);
						push(last_used.val);
					}
					else
						printf("\nError: No variable present\n");
					break;
	
				case '\n':
					if(sp>0)
						printf("\tRESULT: %.8g\n", pop());
					break;
				default:
					printf("Error: unknown command %s\n", s);
					break;
			} 
		} 

	}
	return 0;
}	
