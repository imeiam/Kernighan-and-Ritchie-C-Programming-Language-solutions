#include<stdio.h>
#include<string.h>


	

/*

   Modify the programs entab and detab (written as exercises in Chapter 1) to accept a list of tab stops as arguments. Use the default tab settings if there are no arguments.

*/

#define MAXLENGTH_LINE 100

#define TAB_SIZE 3 // equivalent to 7 spaces. Change tab sizes from 7 to 1 for testing.


int getline_new(char line[],int lim,FILE *fp);

int main(int argc,char *argv[]){

	FILE *fp = fopen("t11b.txt","r");
	char str[100],new_str[100];
	int line_max_len = MAXLENGTH_LINE;
	int len,i;
	char *p = NULL;
	char c;
	int tab_count=0,space_count=0;
	int blank_count=0,new_index=0;
	int total_blank_count=0;
	int tab_size;
	if(argc!=1)
		tab_size = atoi(argv[1]);
	else
		tab_size = TAB_SIZE;
	if(fp!=NULL){

		while(1){			
			len = getline_new(str,MAXLENGTH_LINE,fp);
			if(len == -1)
				break;
			if(len == 0 )
				continue;
			p = str;
			printf("String: ");
			puts(str);
			printf("\nBefore formatting length: %d\n",(int)strlen(str));
			printf("\nBlank lengths: ");
			while((c=*p)){

				if(c == ' '){
					blank_count++;
					p++;
					total_blank_count++;
				}
				else{
					if(blank_count!=0){

						tab_count = blank_count/tab_size;
						space_count = blank_count % tab_size;			
						for(i=0;i<tab_count;i++)
							new_str[new_index++] = '\t';
						for(i=0;i<space_count;i++)
							new_str[new_index++] = ' ';
						printf("\n%d",blank_count);
						blank_count = 0;
					}
					new_str[new_index++] = c;
					p++;
				}
			}
			if(blank_count!=0){
				tab_count = blank_count/tab_size;
				space_count = blank_count % tab_size;			
				for(i=0;i<tab_count;i++)
					new_str[new_index++] = '\t';
				for(i=0;i<space_count;i++)
					new_str[new_index++] = ' ';
				printf("\n%d",blank_count);
				blank_count =0; //reset
			}
			new_str[new_index] = '\0';
			printf("\nAfter formatting length %d\n",(int)strlen(new_str));
			printf("Total blank count: %d \n",total_blank_count);
			putchar('\n');
			new_index = 0; // reset for next line
			total_blank_count = 0;
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
