#include<iostream>
using namespace std;

class A
{
public:
	void foo()
	{
		printf("A类中：1\n");
	}
	virtual void fun()
	{
		printf("A类中：2\n");
	}
};

class B : public A
{
public:
	void foo()
	{
		printf("B类中：3\n");
	}
	void fun()
	{
		printf("B类中：4\n");
	}
};

int main(void)
{
	A a;
	B b;

	A *p = &a; //基类指针
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