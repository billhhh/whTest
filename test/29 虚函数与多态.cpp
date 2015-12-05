#include<iostream>
using namespace std;

class A
{
public:
	void foo()
	{
		printf("A���У�1\n");
	}
	virtual void fun()
	{
		printf("A���У�2\n");
	}
};

class B : public A
{
public:
	void foo()
	{
		printf("B���У�3\n");
	}
	void fun()
	{
		printf("B���У�4\n");
	}
};

int main(void)
{
	A a;
	B b;

	A *p = &a; //����ָ��
	p->foo();
	p->fun();
	cout<<endl;

	p = &b;
	p->foo();
	p->fun();
	cout<<endl;

	B *ptr = (B *)&a;
	ptr->foo();
	ptr->fun();

	return 0;
}