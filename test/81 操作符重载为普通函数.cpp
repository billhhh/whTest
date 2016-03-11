#include <iostream>
using namespace std;

class Add
{
public:
	int para;

	Add(int n):para(n) {}
protected:
private:
};

Add operator+(Add lsh,Add rsh) {

	return lsh.para+rsh.para;
}

int main() 
{
	Add a(5);
	Add b(6);

	Add c = a+b;
	cout<<c.para<<endl;
	return 0; 
}