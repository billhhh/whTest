#include <iostream>]
using namespace std;

int AaddB(int a,int b)
{
	cout<<"第一个add函数"<<endl;
	return a+b;
}

int AaddB(double a,double b)
{
	cout<<"第二个add函数"<<endl;
	return a+b;
}

int main()
{
	AaddB(1,2);
	return 0;
}
