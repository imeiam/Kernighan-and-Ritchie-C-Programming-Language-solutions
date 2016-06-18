
/*
   Write a program to print a histogram of the lengths of words in its input. It is easy to draw the histogram with the bars horizontal.
*/


#include<stdio.h>
#include<ctype.h>

#define IN 1
#define OUT 2
#define MAX_WORD_LENGTH 10


void print_histogram(int arr[]);

int main(void){

	int state = OUT;
	int histogram[MAX_WORD_LENGTH];
	char str[100],c;
	int len,i,test_alpha_num;
	printf("Enter the string: ");
	gets(str);
	len = strlen(str);
	int start=-1,end=-1;
	char *p = str;

	// Set all entries to 0
	memset(histogram,0,MAX_WORD_LENGTH * sizeof(int));

	printf("\nHistogram:\n");
	while(*p){

		test_alpha_num = isalnum(*p);
		if(test_alpha_num && state == OUT){
		
			state = IN;
			start =  p - str;

		}
		else if(!test_alpha_num && state == IN){
			
			end = (p - str) - 1;
			histogram[end - start]++;
			state = OUT;
		}
		p++;
	}

	// If string ends with a word.
	if(state == IN){
		histogram[len-1-start]++;
	}

	print_histogram(histogram);

	return 0;

}


void print_histogram(int arr[]){

	int i=0,j;
	for(;i<MAX_WORD_LENGTH;i++){
		printf("# %d # - ",i+1);
		for(j=0;j<arr[i];j++)
			printf("*");
		printf("\n");
	}
}

