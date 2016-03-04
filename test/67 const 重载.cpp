#include <iostream>
using namespace std;

class A
{
	int num;
public:
	A() {num=5;}
	void disp();
	void disp() const;
	void set(int n) {num=n;}

	void f(int i) {
		cout<<"int"<<endl;
	}

	void f(const int i) {
		cout<<"const int"<<endl;
	}
};

void A::disp() const {
	cout<<num<<endl;
}

void A::disp() {
	cout<<"non-const version of disp()"<<endl;
}

int main() 
{
	A a1;
	a1.set(3);
	a1.disp();
	A const a2;
	a2.disp();
}