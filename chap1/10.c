// Replace tabs by \t, backspace by \b, backslash by \\



#include<stdio.h>
#include<string.h>

#define STATE0 0
#define STATE1 1

int main(void){
	

	char str[50];
	int len;
	int state = STATE0;	


	printf("Enter the input string: ");
	gets(str);
	len = strlen(str);

	
	char *p  = str;
	while(*p){
	
		switch(*p){		

			case '\t':
				printf("\\t");
				break;
			case '\b':
				printf("\\b");
				break;
			case '\\':
				printf("\\\\");
				break;

			default:
				printf("%c",*p);
			
		}
		p++;
	}
	return 0;

}
