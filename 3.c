#include<stdio.h>

int main(void){

	float fahr,celsius;

	int upper,lower,step;


	lower = 0;
	upper = 300;
	step  = 20;


	fahr = lower;


	printf("Fahrenheit - Celsius\n");

	while(fahr <= upper){

		celsius = (5.0/9) * (fahr - 32.0);

		printf("%10.0f - %7.1f\n",fahr,celsius);

		fahr+= step;
	}


	return 0;

}
