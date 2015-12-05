#include<iostream>
using namespace std;

class A
{
public:
	void foo()
	{
		printf("A类中：实foo()\n");
	}
	virtual void fun()
	{
		printf("A类中：虚fun()\n");
	}
};

class B : public A
{
public:
	virtual void foo()
	{
		printf("B类中：虚foo()\n");
	}
	void fun()
	{
		printf("B类中：实fun()\n");
	}
};

class C : public B
{
public:
	void foo()
	{
		printf("C类中：实foo()\n");
	}
	void fun()
	{
		printf("C类中：实fun()\n");
	}
};

int main(void)
{
	A a;
	B b;

	A *ap = &a;
	ap->foo(); //父实子虚
	ap->fun(); //父虚子实
	cout<<endl;

	ap = &b;
	ap->foo();
	ap->fun();
	cout<<endl;

	cout<<"???"<<endl;
// 	B *ptr = (B *)&a;
// 	A *aa = new A();
// 	B *ptr = dynamic_cast<B*>(aa);
// 	if(!ptr)
// 	{
// 		cout << "dynamic cast err!"<<endl;
// 		return 0;
// 	}
// 	ptr->foo(); //为什么是c
// 	ptr->fun(); //为什么是c
// 	cout<<endl;

	C oc;
	B *bp = &b;
	bp->foo();
	bp->fun();
	cout<<endl;

	bp = &oc;
	bp->foo();
	bp->fun(); //为什么不是B中
	cout<<endl;

	return 0;
}