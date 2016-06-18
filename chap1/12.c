#include<stdio.h>
#include<ctype.h>

#define IN 1
#define OUT 2


void print_word(char *str,int start,int end);

int main(void){

	int state = OUT;
	char str[100],c;
	int len,i,test_alpha_num;
	printf("Enter the string: ");
	gets(str);
	len = strlen(str);
	int start=-1,end=-1;

	char *p = str;

	while(*p){

		test_alpha_num = isalnum(*p);
		if(test_alpha_num && state == OUT){
		
			state = IN;
			start =  p - str;

		}
		else if(!test_alpha_num && state == IN){
			
			end = (p - str) - 1;
			print_word(str,start,end);
			state = OUT;
		}
		p++;
	}

	// If string ends with a word.
	if(state == IN){
		print_word(str,start,len-1);
	}

	return 0;

}

void print_word(char *str,int start,int end){

	int i=0;
	for(i=start;i<=end;i++)
		printf("%c",str[i]);
	printf("\n");

}
