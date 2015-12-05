#include <iostream>
using namespace std;

class A
{
public:
	int &mem;
	A(int a):mem(a){};

protected:
private:
};

int main() 
{
	int a=5;
	A *classa = new A(a);

	classa->mem = 111;
	cout<<a<<endl;

	return 0; 
}