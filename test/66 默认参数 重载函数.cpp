#include <iostream>
using namespace std;

class A
{
public:
	void pri(int a) {
		cout<<"a"<<endl;
	}

	void pri(int a,int b=2) {
		cout<<"b"<<endl;
	}

protected:
private:
};

int main() 
{
	A a;
	a.pri(4,5);

	return 0; 
}