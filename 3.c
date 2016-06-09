/*
   Write the function htoi(s) , which converts a string of hexadecimal digits (including an optional 0x or 0X) into its equivalent integer value.
   The allowable digits are 0 through 9, a through f, and A through F

   */



#include<stdio.h>
#include<string.h>


#define HEX_LOWER(N) (N >= 'a' && N <= 'f')
#define HEX_HIGHER(N) (N >= 'A' && N <= 'F')
#define HEX_NUMBER(N) (N >= '0' && N <= '9')
#define IS_HEX(N) ( HEX_LOWER(N) || HEX_HIGHER(N) || HEX_NUMBER(N) )


int htoi(char str[]);

int main(void){

	char str[20];
	printf("\nEnter the hex value: ");
	fgets(str,20,stdin);
	printf("\n %d ",str[strlen(str)-1]);
	int val = htoi(str);
	if( val == -1 )
		printf("\nError!\n");
	else
		printf("\nEquivalent Value: %d \n ",val);
	return 0;
}

int htoi(char str[]){
	
	int len = strlen(str);
	str[len]='\0';
	len--;
	printf("\nLength: %d",len);
	int sum = 0;
	int i = 0 ;
	register char c ;
	if(len>0){
		
		// if if two characters are 0x || 0X
		if(str[0] == '0' && len > 2 &&  ( str[1] == 'x' || str[1] == 'X' ) ){
			i = 2;	
		}
		for(;i<len;i++){
			
			c = str[i];
			printf("\n%c\n",c);
			if(!IS_HEX(c)) return -1;

			if(HEX_NUMBER(c)){
				sum = sum * 16 + c - '0';
			}
			else if (HEX_LOWER(c)){
				sum = sum * 16 + c - 'a';
			}
			else{ // Higher
				sum = sum * 16 + c - 'A';
			}
		}
		return sum;
	}
	return -1; // if len is less than 0
}
