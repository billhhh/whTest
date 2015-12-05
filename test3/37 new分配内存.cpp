#include <iostream>
using namespace std;

class A
{
public:
	A()
	{
		//cout<<"A ¹¹Ôìº¯Êý"<<endl;
	}

	int a;
};

int main()
{
	A *ap = new A[1<<25];

	int tmp;
	cin>>tmp;

	if (tmp == 1)
	{
		for (int i=0;i<1<<25;i++)
		{
			ap[i].a=1;
		}
	}

	while (true)
	{

	}

	return 0;
}
