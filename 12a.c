#include<stdio.h>
#include<string.h>


	

/*
   Modify the programs entab and detab (written as exercises in Chapter 1) to accept a list of tab stops as arguments. Use the default tab settings if there are no arguments.
*/


// ARG1 - TABSTOP

#define MAXLENGTH_LINE 100

#define TAB_SIZE 7 // equivalent to 7 spaces. Change tab sizes from 7 to 1 for testing.
#define START_COL 0
#define TAB_PERIOD 5

int main(int argc,char *argv[]){

	FILE *fp = fopen("t12a.txt","r");
	char str[100];
	int line_max_len = MAXLENGTH_LINE;
	int len,i;
	char *p = NULL;
	char c;
	int tab_size,tab_period,start_col; 
	// Default
	tab_size = TAB_SIZE;
	tab_period = TAB_PERIOD;
	start_col = 0;
	switch(argc){

		case 2:
			tab_size = atoi(argv[1]);
			break;
		case 3:
			tab_size = atoi(argv[1]);
			if(argv[2][0] == '+')
				tab_period = atoi(argv[2]);
			else if(argv[2][0] == '-'){
				argv[2][0] = '+';
				start_col = atoi(argv[2]);
			}
			break;

		case 4:
			tab_size = atoi(argv[1]);
			int i=2;
			for(;i<4;i++){
				if(argv[i][0] == '+')
					tab_period = atoi(argv[i]);
				else if(argv[i][0] == '-'){
					argv[i][0] = '+';
					start_col = atoi(argv[i]);
				}
			}



	}
	printf("\n %d - -  %d \n ",tab_period,start_col); 
	if(fp!=NULL){
		int ctr=0;
		while(1){			
			len = getline_new(str,MAXLENGTH_LINE,fp);
			if(len == -1)
				break;
			if(len == 0 )
				continue;
			p = str;
			while((c=*p)){

				if((p-str)%tab_period == 0  && p-str >= start_col)
					putchar('\t');
				if(c == '\t')
					for(i=0;i<tab_size;i++)
						putchar(' ');
				else
					putchar(c);
				p++;
				
			}
			putchar('\n');
		}
		fclose(fp);
	}

	return 0;
}


int getline_new(char line[],int lim,FILE *fp){

	int c,i;
	for(i=0;i<lim-1 && (c=fgetc(fp))!=EOF && c!='\n';i++)
		line[i] = c;
	line[i] = '\0';
	if(c == EOF)
		return -1;
	else
		return i;

}
