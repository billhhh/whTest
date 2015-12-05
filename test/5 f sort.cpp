#include<iostream>
#include<algorithm>

using namespace std;

void change(int & n)
{
	n=5;
}

int main()
{
	int a=1;
	cout<<a<<endl;

	change(a);
	cout<<a<<endl;

	return 0;
}
