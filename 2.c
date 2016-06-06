#include<stdio.h>

/*
   Write a loop equivalent to the for loop above without using && or ||.
   */


#define CHARACTER_LIMIT 10
int main(void){

		
	int c,i;
	int lim = CHARACTER_LIMIT;
	
	i=0;
	while(i<lim-1){

		c = getchar();
		if( c != EOF ){
	
			if(c == '\n')
				break;
			else{
				putchar(c);
			}
		}
		else{
			break;
		}
		i++;
	}
	return 0;

}

