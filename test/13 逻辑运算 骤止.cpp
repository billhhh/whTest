#include <iostream>

using namespace std;

int main()
{
	int x,y;
	x=y=1;
	++x || ++y;

	cout<<(5||6)<<endl;
	cout<<y<<endl;
	return 0;
}