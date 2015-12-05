#include <iostream>
using namespace std;

int main()
{
	cout<<sizeof("n\x45y\123\t")<<endl;
	cout<<"\3"<<"  "<<sizeof("\x45")<<endl;
	cout<<"\60"<<"  "<<sizeof("\123")<<endl;

	return 0;
}
