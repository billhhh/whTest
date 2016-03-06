#include <iostream>
using namespace std;

int BTcount(int x) {

	int count = 0;
	while(x) {
		x=x&(x-1);
		count++;
	}

	return count;
}

int main() 
{
	cout<<BTcount(9999)<<endl;
	return 0; 
}