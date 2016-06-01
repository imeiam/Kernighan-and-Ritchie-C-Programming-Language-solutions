// All possible values of getchar!=EOF is 1 or 0

#include<stdio.h>

int main(void){


	FILE *fp = fopen("test.txt","r");
	char c;


	if(fp!=NULL){
		printf("\nPossible values of expression: \n");		
		while(1){
			c = fgetc(fp);
			printf("%d \n",c != EOF);
			if(c==EOF)
				break;
		}		
		fclose(fp);
	}
	else{
		printf("Error: File Open error");
	}

	return 0;

}
