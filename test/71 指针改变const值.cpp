#include <iostream>
using namespace std;

void ShowValue(const int &i) {
	cout<<i<<endl;
}

int main() 
{
	const int j=5;
	void *p=(void *)&j;
	int *ptr=(int *)p;
	(*ptr)++;
	//cout<<*ptr<<endl;
	ShowValue(j);

	return 0; 
}