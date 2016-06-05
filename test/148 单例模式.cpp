#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <cassert>
#include <time.h>
#include <queue>
#include <map>
#include <stack>
#include <bitset>
#include <string>
#include <sstream>
#define INF 0x3f3f3f3f

#define PRINT(x) cout<<x<<endl;

using namespace std;

template <class Type>
Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;    
}

//======================================================

class CSingleton  
{  
private:  
	CSingleton()   //���캯����˽�е�  
	{  
	}  
	static CSingleton *m_pInstance;  
	class CGarbo   //����Ψһ��������������������ɾ��CSingleton��ʵ��  
	{  
	public:  
		~CGarbo()  
		{  
			printf("delete");
			if(CSingleton::m_pInstance)  
				delete CSingleton::m_pInstance;  
		}  
	};  
	static CGarbo Garbo;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������
public:  
	static CSingleton * GetInstance()  
	{  
		if(m_pInstance == NULL)  //�ж��Ƿ��һ�ε���  
			m_pInstance = new CSingleton();  
		return m_pInstance;  
	}

	void pfunc() {
		PRINT("success");
	}
};  

CSingleton* CSingleton::m_pInstance = nullptr;

int main()
{
	//freopen("input.txt","r",stdin);
	auto instance = CSingleton::GetInstance();
	instance->pfunc();

	return 0;
}