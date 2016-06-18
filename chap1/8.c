// No of newlines, tabs, blanks.


#include<stdio.h>

int main(void){


	FILE *fp = fopen("test.txt","r");
	char c;
	int blank,newline,tab;
	blank = newline = tab = 0;
	if(fp!=NULL){

		while((c = fgetc(fp))!=EOF){
			printf("%c",c);
			switch(c){
			
			case ' ':
				blank++;
				break;

			case '\t':
				tab++;
				break;

			case '\n':
				newline++;
				break;

			default:
				// Ignore
				break;

			}	
		}
		fclose(fp);

		printf("\nNo of Newlines: %d",newline); 
		printf("\nNo of Blanks: %d",blank); 
		printf("\nNo of Tabs: %d",tab); 
	}
	else{
		printf("Error: File Open error");
	}

	return 0;

}
