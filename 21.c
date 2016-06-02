#include<stdio.h>
#include<string.h>


	

/*
   Write a program entab that replaces strings of blanks with the minimum number of tabs and blanks to achieve the same spacing. 
   Use the same stops as for detab.

*/

#define MAXLENGTH_LINE 100

#define TAB_SIZE 3 // equivalent to 7 spaces. Change tab sizes from 7 to 1 for testing.


int getline_new(char line[],int lim,FILE *fp);

int main(void){

	FILE *fp = fopen("t21.txt","r");
	char str[100],new_str[100];
	int line_max_len = MAXLENGTH_LINE;
	int len,i;
	char *p = NULL;
	char c;
	int tab_count=0,space_count=0;
	int blank_count=0,new_index=0;
	int total_blank_count=0;
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

						tab_count = blank_count/TAB_SIZE;
						space_count = blank_count % TAB_SIZE;			
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
				tab_count = blank_count/TAB_SIZE;
				space_count = blank_count % TAB_SIZE;			
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
