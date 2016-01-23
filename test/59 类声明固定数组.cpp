#include <iostream>
using namespace std;

#define GRAGH_LENGTH 180
#define GRAGH_WIDTH 128

typedef int (Mytype[GRAGH_LENGTH])[GRAGH_WIDTH];

class Test
{
public:
	Mytype a;
		
protected:


private:


};

int main() 
{
	Test t;

	cout<<t.a<<endl;
	cout<<&t.a[0][1]<<endl;

	cout<<t.a[0][1]<<endl;
	t.a[0][1] = 2;
	cout<<t.a[179][127]<<endl;
	
	return 0;
}