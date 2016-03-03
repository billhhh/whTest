#include <iostream>
using namespace std;

class B
{
public:
	int bm1;

	B():bm1(5) {

	}
protected:
private:
};

class A
{
public:
	//int bm1;

	B ab;
protected:
private:
};

class C : public A , public B
{
public:
protected:
private:
};

int main() 
{
	C c;
	c.ab.bm1 = 6;
	cout<<c.ab.bm1<<endl;

	cout<<c.bm1<<endl;

	return 0; 
}