#include <iostream>
using namespace std;

class Test
{
public:
	int *a;
};

int main() 
{
	Test *t = new Test();
	int aa = 1314520;
	t->a = &aa;

	Test *t2 = new Test(*t);

	cout<<t->a<<endl;
	cout<<t2->a<<endl;

	return 0; 
}