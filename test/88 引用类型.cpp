#include <iostream>
using namespace std;

int main() 
{
	int a[5] = {1};
	int &b = a[2];

	cout<<a[2]<<endl;
	b = 3;
	cout<<a[2]<<endl;

	return 0; 
}