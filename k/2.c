/*
Write a program that will print arbitrary input in a sensible way. As a minimum, it should print non-graphic characters in octal or hexadecimal according to local custom, and break long text lines.
   */


#include<stdio.h>

#define OCTAL 1
#define HEX 2
#define DEFAULT HEX

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



void rev(char *str){

	char *p,*t;
	for(t=str;*t!='\0';t++);
	t--;
	p = str;
	char c;
	if(t-p<1)
		return;
	while(p!=t && t+1!=p){
		c= *p;
		*p = *t;
		*t = c;
		p++;
		t--;
	}
}


char *itoa(int value, char *str, int base)
{
    char *p;
    p = str;
    int sign = 1;
    char *ref = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (str == NULL || base < 2)
        return NULL;
    if (value < 0) {
	sign = -1;
    }
    while(value!=0){
	*p++ = ref[sign*(value%base)];
	value/=base;
    }
    if(sign==-1)
	    *p++ = '-';
    *p = '\0';
    puts(str);
    rev(str);
    return str;
}

int type = DEFAULT;

int main(int argc,char *argv[]){
	if(argc>1){
		if(strcasecmp(argv[1],"-o")==0){
			type = OCTAL;
		}
		else if( strcmp(argv[1],"-x") ==0){
			type = HEX;
		}
	}
	puts("\nEnter the words:");
	char line[MAXLEN];
	char *p;
	char number[100];
	while(getlinex(line,MAXLEN,stdin)>0){
		p = line;
		while(*p){		
			// Printable
			if(*p>32 && *p<127){
				putchar(*p);
			}
			else if(type==OCTAL){
				putchar('0');
				itoa((int)*p,number,8);
			}
			else{
				putchar('0');
				putchar('x');
				itoa((int)*p,number,16);
			}
			p++;
		}
		putchar('\n');
	}
	return 0;
}
