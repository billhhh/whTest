#include <iostream>
using namespace std;

int main()
{

	int a[] = {
		#include "testheadcompile.h"
		,5
	};

	cout<<a[4]<<endl;

	return 0;
}
