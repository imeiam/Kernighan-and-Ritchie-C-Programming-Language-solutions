/*


	Find the longest line among a set of given lines.

*/



#include<stdio.h>
#define MAXLINE 1000


int getline_new(char line[],int maxline);
void copy(char to[],char from[]);




int main(void){

	int len;
	int max;

	char line[MAXLINE];
	char longest[MAXLINE];


	max = 0;
	

	printf("Enter the lines: ( Single $ to terminate input)\n");
	while((len = getline_new(line,MAXLINE)) > 0){

		if(len > max){

			max = len;
			copy(longest,line);

		}

	}

	if(max>0){
		printf("\nLongest: ");
		puts(longest);
		printf("\nLength: %d\n",max);
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


void copy(char to[],char from[]){

	int i;
	i =0;
	while((to[i] = from[i]) != '\0')
		i++;
}
