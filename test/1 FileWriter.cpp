#include <iostream>
#include <fstream> //文件输入输出流

using namespace std;

int main(void)
{
	ofstream myfile("D:\\TESTCASE\\testout.txt",ios::out);  //example.txt是你要输出的文件的名字
	if(!myfile)
	{
		cout<<"error !";
	}

	else
	{
		myfile<<"My first out! O(∩_∩)O~";
		myfile.close();
	}

	return 0;
}
