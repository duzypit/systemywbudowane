#include <stdio.h>

int main(void){

	int x = 10;
	int y = 14;

	x = x ^ y; 									//x = 4
	printf("x after first xor = %d\n", x);
	y = x ^ y;									//y = 10
	printf("y after sexond xor = %d\n", y );
	x = x ^ y;									//x = 14

	printf("result: x = %d, y = %d\n", x , y);

	return 0;
}