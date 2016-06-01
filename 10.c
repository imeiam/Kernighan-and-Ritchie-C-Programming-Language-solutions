// Replace consective blanks by a single blank.



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

			case ' ':
				if(state == STATE0){
					printf(" ");
					state = STATE1;
					p++;
					continue;
				}
				else{
					p++;
					continue;
				}
				break;
			default:
				if(state == STATE1)
					state = STATE0;
				printf("%c",*p);
				p++;
		}
	}
	return 0;

}
