#include<iostream>
using namespace std;

class A
{
public:
	void foo()
	{
		printf("A���У�ʵfoo()\n");
	}
	virtual void fun()
	{
		printf("A���У���fun()\n");
	}
};

class B : public A
{
public:
	virtual void foo()
	{
		printf("B���У���foo()\n");
	}
	void fun()
	{
		printf("B���У�ʵfun()\n");
	}
};

class C : public B
{
public:
	void foo()
	{
		printf("C���У�ʵfoo()\n");
	}
	void fun()
	{
		printf("C���У�ʵfun()\n");
	}
};

int main(void)
{
	A a;
	B b;

	A *ap = &a;
	ap->foo(); //��ʵ����
	ap->fun(); //������ʵ
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
// 	ptr->foo(); //Ϊʲô��c
// 	ptr->fun(); //Ϊʲô��c
// 	cout<<endl;

	C oc;
	B *bp = &b;
	bp->foo();
	bp->fun();
	cout<<endl;

	bp = &oc;
	bp->foo();
	bp->fun(); //Ϊʲô����B��
	cout<<endl;

	return 0;
}