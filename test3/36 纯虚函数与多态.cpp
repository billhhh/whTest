//小结：1、有virtual才可能发生多态现象
// 2、不发生多态（无virtual）调用就按原类型调用
#include<iostream>
using namespace std;

class Base
{
public:
	virtual void f1(float x)=0;
// 	{
// 		cout<<"Base::f1(float)"<< x <<endl;
// 	}
// 	virtual void f2(float x)
// 	{
// 		cout<<"Base::f2(float)"<< x <<endl;
// 	}
// 	void f3(float x)
// 	{
// 		cout<<"Base::f3(float)"<< x <<endl;
// 	}
};

class Derived : public Base
{
public:
	virtual void f1(float x)
	{
		cout<<"Derived::f1(float)"<< x <<endl;   //多态、覆盖
	}
// 	void f2(int x)
// 	{
// 		cout<<"Derived::f2(int)"<< x <<endl;     //隐藏
// 	}
// 	void f3(float x)
// 	{
// 		cout<<"Derived::f3(float)"<< x <<endl;   //隐藏
// 	}
};

int main(void)
{
	Derived d;
	Base *pbase = &d;
	Derived *pderi = &d;

	// Good : behavior depends solely on type of the object
	pbase->f1(3.14f);   // Derived::f1(float) 3.14
	pderi->f1(3.14f);   // Derived::f1(float) 3.14
	cout<<endl;

	// Bad : behavior depends on type of the pointer
// 	pbase->f2(3.14f);   // Base::f2(float)  3.14
// 	pderi->f2(3.14f);   // Derived::f2(int) 3
// 	cout<<endl;
// 
// 	// Bad : behavior depends on type of the pointer
// 	pbase->f3(3.14f);   // Base::f3(float) 3.14
// 	pderi->f3(3.14f);   // Derived::f3(float) 3.14

	return 0;
}