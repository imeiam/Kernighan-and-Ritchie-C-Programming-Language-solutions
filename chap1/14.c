/*

  Write a program to print a histogram of the frequencies of different characters in its input.

*/


#include<stdio.h>
#include<ctype.h>

void print_histogram(int char_count[]);
int main(void){

	char str[100];
	int all_char_count[128];
	int len,i;
	char *p;
	printf("Enter the string: ");
	fgets(str,100,stdin);
	puts(str);

	memset(all_char_count,0, 128 * sizeof(int));

	p = str;
	while(*p){
		all_char_count[(int)(*p)]++;
		p++;
	}
	
	print_histogram(all_char_count);

	return 0;

}


void print_histogram(int char_count[]){

	int i=0,j;
	for(;i<128;i++){


		if(char_count[i]>0){
			
			if(i==10)
				continue;
			printf("| %c | -  ",(char) i);
			
			for(j=0;j<char_count[i];j++)
				printf("*");
			printf("\n");
		}

	}

}
