/* 
* 
* funtion: 注意，如下被注释的代码，都是访问不到的
* 
* Date:2015-7-29
* 
*    Author: Bill Wang
*/

#include<iostream>
using namespace std;

//在类O中分别定义了三个不同访问类型的函数
class O{
public:
	void F2()
	{
		cout<<"this is O's public function F2"<<endl;
	}
private:
	void F1();
protected:
	void F3();
};

//类P保护继承于O
class P:protected O{
public:
	/*
	void test_F1()
	{
		F1();
	}
	*/
	void test_F2()
	{
		F2();
	}
	void test_F3()
	{
		F3();
	}
};

//类Q公有继承于O
class Q:public O{
public:
	/*
	void test_F1()
	{
		F1();
	}
	*/
	void test_F2()
	{
		F2();
	}
	void test_F3()
	{
		F3();
	}
};

//类R私有继承于O
class R:private O{
public:
	/*
	void test_F1()
	{
		F1();
	}
	*/
	void test_F2()
	{
		F2();
	}
	void test_F3()
	{
		F3();
	}
};

//定义在类体内或体外都一样
void O::F1()
{
	cout<<"this is O's private function F1"<<endl;
}
void O::F3()
{
	cout<<"this is O's protected function F3"<<endl;
}

//主函数
int main()
{
	O o;
	P p; //保护继承
	Q q; //公有继承
	R r; //私有继承

	cout<<"O:"<<endl;
	//o.F1(); //私有方法
	o.F2(); //公有方法
	//o.F3(); //保护方法
	cout<<endl;

	//三种继承：成员访问情况一样

	cout<<"P:"<<endl;
//	p.test_F1(); //私有方法访问不到
	p.test_F2();
	p.test_F3();
	//p.F1();
	//p.F2();
	//p.F3();
	cout<<endl;

	cout<<"Q:"<<endl;
//	q.test_F1();
	q.test_F2();
	q.test_F3();
	//q.F1();
	q.F2();
	//q.F3();
	cout<<endl;

	cout<<"R:"<<endl;
//	r.test_F1();
	r.test_F2();
	r.test_F3();
	//r.F1();
	//r.F2();
	//r.F3();

	return 0;
}