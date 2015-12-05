#include <stdlib.h> 
#include <stdio.h>

int main(void) 
{ 
	int number = 10;
	number = number<<5;

	number += 10;
	char string[25];

	itoa(number, string, 2); 
	printf("integer = %d string = %s\n", number, string); 

	return 0; 
}