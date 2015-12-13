#include <iostream>
#define eps 1e-8

using namespace std;

int main() 
{
	double n,m;

	cin>>n;
	while( cin>>m ) {

		if( 999-m<eps )
			break;

		cout<<n-m<<endl;
		n=m;
	}

	cout<<"End of Output"<<endl;

	return 0; 
}