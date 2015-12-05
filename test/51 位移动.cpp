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
	int number = -1073741825;
	cout<<"左移之前"<<endl;
	showInBinary(number);

	number = number<<1;

	cout<<"左移之后"<<endl;
	showInBinary(number);

	return 0; 
}