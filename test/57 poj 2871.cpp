#include <iostream>
#define eps 1e-8

using namespace std;

int main() 
{
	//freopen("input.txt", "r", stdin);
	double n,m;

	cin>>n;
	while( cin>>m ) {

		//if( m == 999 )
		if( 999-m<eps )
			break;

		printf("%.2f\n",m-n);

		n=m;
	}

	cout<<"End of Output"<<endl;

	return 0; 
}