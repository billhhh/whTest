#include <iostream>
using namespace std;

struct A
{
	void foo(){printf("foo");}
	virtual void bar(){printf("bar");}
	A(){bar();}
};

struct B:A
{
	void foo(){printf("b_foo");}
	void bar(){printf("b_bar");}
};

int main()
{
	char arr[10]="abcdefg";

	cout<<sizeof(arr)+strlen(arr);

// 	int testArray[8];
// 	cout<<sizeof(testArray)<<endl;
// 	cout<<sizeof(testArray[0])<<endl;

// 	A *p = new B;
// 	p->foo();
// 	p->bar();

	return 0;
}