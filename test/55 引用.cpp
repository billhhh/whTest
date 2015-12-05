#include <iostream>
using namespace std;

int main() 
{
	int a=5;
	int &aa = a;
	int *aaa;
	aaa = &aa;

	*aaa = 4657;
	cout<<a<<endl;

	return 0; 
}