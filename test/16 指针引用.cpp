#include <iostream>
using namespace std;

void fun5(int *&);  //函数声明，声明时参数不用写变量名

int main()
{
	int a,*p=&a;
	cout<<"在main函数中p的地址是："<<&p<<"p中存放的地址是（即a的地址）："<<p<<endl;
	fun5(p);

	return 0;
}

void fun5(int *& rp) //函数定义，具体实现过程，需要写变量名，指针的引用
{
	cout<<"在fun5函数中rp的地址是："<<&rp<<"rp中存放的地址是："<<rp<<endl;
	return;
}
