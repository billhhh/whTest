#include <iostream>
using namespace std;

#define GRAGH_LENGTH 180
#define GRAGH_WIDTH 128

typedef int (Mytype[GRAGH_WIDTH])[GRAGH_LENGTH];

class Test
{
public:
	Mytype a;
	Mytype get() {
		return a;
	}

protected:


private:


};

int main() 
{
	Test t;

	cout<<t.a<<endl;
	cout<<t.get()<<endl;
	cout<<&t.a[0][1]<<endl;



	return 0;
}