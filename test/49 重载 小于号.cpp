#include <iostream>
#include <assert.h>
using namespace std;

typedef struct structPort
{
	int moduleId;
	int paraId;

	bool operator < (const structPort &port) const
	{
		if( moduleId < port.moduleId ) { //С��ֱ�ӷ���true
			return true;
		}else if( moduleId > port.moduleId ) { //���ڷ���false
			return false;
		}else {

			//���moduleIdһ���������Ƚ�paraId�������ܶ�һ��
			if( paraId < port.paraId )
				return true;
			else if(paraId > port.paraId)
				return false;
			else
				assert(false);
		}
	}

}whPort;  //һ�����ڶ��壬��ȫ����һ��port

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
