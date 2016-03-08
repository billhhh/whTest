#include <iostream>
using namespace std;

//const int j=5;

void ShowValue(const char* i) {
    cout<<i<<endl;
}

int main() 
{
	const char j[]="123";
	void *p=(void *)&j;
	char *ptr=(char *)p;
	ptr[1]='d';
	ShowValue(j);

    return 0; 
}