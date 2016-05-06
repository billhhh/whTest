#include <iostream>
using namespace std;

void tmp(int t) {
	cout<<t<<endl;
}

int main(int argc,char* argv[])
{
	volatile int ic=12;
	volatile int i=10;
	int a=i;
	volatile int ib=11;
	tmp(a);
	tmp(ib);
	tmp(ic);

	_asm{
		mov dword ptr [ebp-4],80
	}

	int b=i;
	tmp(b);

	return 0;
}