#include <iostream>
using namespace std;

void ShowValue(const int &i) {
	cout<<i<<endl;
}

int main() 
{
	int i=5;
	const int j=i;
	void *p=(void *)&j;
	int *ptr=(int *)p;
	(*ptr)++;
	cout<<j<<endl;
	//ShowValue(j);

	return 0; 
}