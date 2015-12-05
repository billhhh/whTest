#include <iostream>

using namespace std;

int zhou=16;

int main()
{
	int zhou=12; //局部变量 

	if (true)
	{
		int zhou = 10;

		if (true)
		{
			cout<<::zhou<<endl;
		}
	}
}
