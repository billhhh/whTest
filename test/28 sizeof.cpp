#include<iostream>

using namespace std;

int main()
{
	cout << "sizeof(char) == " << sizeof(char) << endl;
	cout << "sizeof(char*) == " << sizeof(char*) << endl;
	cout<<"sizeof(string) == " << sizeof(string) << endl;

	string strArr1[] = { "Trend", "Micro", "Soft" };
	cout << "sizeof(strArr1) == " << sizeof(strArr1) << endl;

	return 0;
}