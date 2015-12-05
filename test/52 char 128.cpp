#include <stdlib.h> 
#include <stdio.h>
#include <iostream>

using namespace std;

void showInBinary(int number) {

	char string[100];

	itoa(number, string, 2); 
	printf("integer = %3d string = %s\n", number, string);
}

int main() 
{ 
// 	char c = 128;
// 
// 	char cc = c;
// 	unsigned int ui = c;
// 	int i = c;
// 	double d = c;

// 	int a = 0xAA30;
// 	char c = a;
// 	printf("%c",c);

	char c = -1;
	showInBinary(c);

	return 0; 
}