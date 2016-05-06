#include <iostream>
using namespace std;

int main(int argc,char* argv[])
{
	int i=10;
	int a=i;
	cout<<a<<endl;
	_asm{
		mov dword ptr [ebp-4],80
	}
	int b=i;
	cout<<b<<endl;
	getchar();
}