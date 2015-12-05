#include <iostream>
#include <assert.h>
using namespace std;

typedef struct structPort
{
	int moduleId;
	int paraId;

	bool operator < (const structPort &port) const
	{
		if( moduleId < port.moduleId ) { //小于直接返回true
			return true;
		}else if( moduleId > port.moduleId ) { //大于返回false
			return false;
		}else {

			//如果moduleId一样，继续比较paraId，不可能都一样
			if( paraId < port.paraId )
				return true;
			else if(paraId > port.paraId)
				return false;
			else
				assert(false);
		}
	}

}whPort;  //一个出口定义，完全定义一个port

int main()
{
	whPort port1;
	port1.moduleId = 2;
	port1.paraId = 2;

	whPort port2;
	port2.moduleId = 2;
	port2.paraId = 2;

	if( port1 < port2 )
		cout << "right" <<endl;
	else
		cout << "wrong" <<endl;

	return 0;
}
