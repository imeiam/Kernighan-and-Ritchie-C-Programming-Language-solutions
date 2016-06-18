/*
   Our version of getword does not properly handle underscores, string constants, comments, or preprocessor control lines. Write a better version.

   */

#include<stdio.h>

#define BUFSIZE 1000


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


// getword returns the length of the word.
// Word can begin with an underscore.
int getword(char *word,int lim){
	
	int c;
	char *w = word;

	while(isspace((c = getch())));
	if(c=='$')
		return -1;
	// Assume end of input
	if(c!=EOF && c!='/' && c!='*' && c!='"' && c!='#')
		*w++=c;
	if(!isalpha(c) && c!='_'){
		*w = '\0';
		return w-word;
	}
	for(; --lim>0; w++){
		*w = getch();

		if(!isalnum(*w) && *w!='_'){
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return w-word;
}
int main(void){
	char line[100];
	puts("Results: ");
	while(getword(line,100)!=-1){
		if(line[0]!='\0')
			puts(line);
	}
	return;
}
