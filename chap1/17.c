/*
   Print lines that have more than 80 characters.
*/



#include<stdio.h>
#define MAXLINE 1000


#define THRESHOLD_TO_PRINT 80

int getline_new(char line[],int maxline);




int main(void){

	int len;
	int max;

	char line[MAXLINE];
	char longest[MAXLINE];

	max = 0;

	printf("Enter the lines: ( Single $ to terminate input)\n");
	while((len = getline_new(line,MAXLINE)) > 0){

		if(len > THRESHOLD_TO_PRINT){

			printf("Line:  ");
			puts(line);
			printf("\nLength: %d\n",len);
		}

	}

	return 0;
}


int getline_new(char line[],int lim){


	int c,i;
	for(i=0;i<lim-1 && (c=getchar())!=EOF && c!='\n' && c!='$' ;i++)
		line[i] = c;
	line[i] = '\0';
	if(c=='$'){
		getchar();
		// Remove \n from input.
	}
	// Single $ terminates the input. $ as EOF.
	return i;

}

