#include<stdio.h>

int main(void){

	float fahr,celsius;

	int upper,lower,step;


	lower = 0;
	upper = 100;
	step  = 20;


	celsius = lower;


	printf("Celsius - Fahrenheit\n");

	while(celsius <= upper){

		fahr = ((9.0/5) * celsius) + 32.0;

		printf("%7.0f - %10.1f\n",celsius,fahr);

		celsius+= step;

	}


	return 0;

}
