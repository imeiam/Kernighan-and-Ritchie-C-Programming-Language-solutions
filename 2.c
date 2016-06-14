/*
   Extend atof to handle scientific notation of the form 
   123.45e-6 where a floating-point number may be 
   followed by e or E and an optionally signed exponent.
   */

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

double atof(char s[]){

	double val,power,exp=0.0;
	int i,sign,exp_sign;
	int len = strlen(s);
	for(i=0;isspace(s[i]);i++); // Skip white space
	sign = ( s[i] == '-' ) ? -1 : 1;
	if ( s[i] == '+' || s[i] == '-' )
		i++;
	for( val = 0.0; isdigit(s[i]);i++)
		val = 10.0 * val + ( s[i] - '0' );
	if(s[i] == '.')
		i++;
	for(power = 1.0; isdigit(s[i]);i++){
		val = 10.0 * val + ( s[i] - '0' );
		power*=10.0;
	}	
	if(i<len){
		// If the string is not completely processed
		if(s[i] == 'e' || s[i] == 'E')
			i++;
		else 
			return -1; // Error
		exp_sign = ( s[i] == '-' ) ? -1 : 1;
		if ( s[i] == '+' || s[i] == '-' )
			i++;
		for( exp = 0.0; isdigit(s[i]);i++)
			exp = 10.0 * exp + ( s[i] - '0' );
	}
	return sign * val / power * pow(10,exp*exp_sign);

}
int main(void){
	puts("Enter the number: ");
	char str[100];
	fgets(str,100,stdin);
	str[strlen(str)-1] = '\0'; // Avoid newline from fgets
	printf("\nResult: %lf ",atof(str));
	return 0;
}
