#include <iostream>]
using namespace std;

int AaddB(int a,int b)
{
	cout<<"��һ��add����"<<endl;
	return a+b;
}

int AaddB(double a,double b)
{
	cout<<"�ڶ���add����"<<endl;
	return a+b;
}

int main()
{
	AaddB(1,2);
	return 0;
}
