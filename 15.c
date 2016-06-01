#include<stdio.h>


double convert_fahr_to_celsius(double fahr){ return ((5.0/9) * (fahr - 32.0));  }


int main(void){

	float fahr,celsius;

	int upper,lower,step;


	lower = 0;
	upper = 300;
	step  = 20;


	fahr = lower;


	printf("Fahrenheit - Celsius\n");

	while(fahr <= upper){

		celsius = convert_fahr_to_celsius(fahr);

		printf("%10.0f - %7.1f\n",fahr,celsius);

		fahr+= step;
	}


	return 0;

}
