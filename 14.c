/* Swap with a macro two variables of type t */


#include<stdio.h>

#define swap(t, x, y) x = x + y;y = x - y;x = x - y;


int main(void){

	int x = 10,y=20;
	swap(int,x,y);
	printf("\n x = %d y = %d \n",x,y);
	return 0;
}
