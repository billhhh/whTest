#include <iostream>
using namespace std;

int main(int argc,char *argv[])
{
	int a = 6;
	int b[5];

	cout<<oct<<&argc<<endl;
	cout<<oct<<&a<<endl;
	cout<<oct<<b<<endl;
	cout<<oct<<argv<<endl;


	while(argc-- > 1)
		printf("%s\n",*++argv);

	cout<<a<<endl;
	cout<<b<<endl;

	return 0; 
}
