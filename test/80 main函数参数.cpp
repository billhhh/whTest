#include <iostream>
using namespace std;

int main(int argc,char *argv[],int a,int b)
{

	cout<<argc<<endl;
	
	while(argc-- > 1)
		printf("%s\n",*++argv);

	cout<<a<<endl;
	cout<<b<<endl;

	return 0; 
}
