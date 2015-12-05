#include <iostream>

using namespace std;

int *globalP;
int *global2P;

void test() {
	int tmp = *globalP;
	global2P = &tmp;
}

void test2() {
	int aa[100] = {0};
}


int main()
{
	int a = 8;
	globalP = &a;
	test();
	cout<<*global2P<<endl;

	*global2P = 5;
	//test2();
	int aa[100] = {0};
	cout<<*global2P<<endl;

	return 0;
}
