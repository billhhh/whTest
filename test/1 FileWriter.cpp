#include <iostream>
#include <fstream> //�ļ����������

using namespace std;

int main(void)
{
	ofstream myfile("D:\\TESTCASE\\testout.txt",ios::out);  //example.txt����Ҫ������ļ�������
	if(!myfile)
	{
		cout<<"error !";
	}

	else
	{
		myfile<<"My first out! O(��_��)O~";
		myfile.close();
	}

	return 0;
}
