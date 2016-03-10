#include <iostream>
using namespace std;

class ClassSize{
	double num;
	char name[55];
};

int main() 
{
	auto sizeOfClass = sizeof(ClassSize);
	cout<<sizeOfClass<<endl;

	return 0; 
}