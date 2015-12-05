#include <iostream>

using namespace std;

int main()
{
	string str("This is bill here.    Hello worldT!!  \n\n try");
	int n = str.find("T");
	cout<<n<<endl;

	cout<<str.npos<<endl;

	return 0;
}
