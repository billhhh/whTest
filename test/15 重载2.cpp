#include <iostream>
using namespace std;

int max(int a,int b)
{
	return a<b?b:a;
}

int max(int a,int b,int c=0)
{
	cout<<"c == "<<c<<endl;
	return a<b?b:a;
}

int main()
{
	max(5,3,1);
	return 0;
}
