#include <iostream>
using namespace std;

int main() 
{
	const int **p1;
	int *const *p2;

	int i=5;
	int j=6;

	const int *ptr1=&i;
	int *const ptr2=&j;

	p1=&ptr1;
	p2=&ptr2;

	cout<<**p1<<endl;
	cout<<**p2<<endl;

	return 0; 
}