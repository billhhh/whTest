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
	CSingleton()   //构造函数是私有的  
	{  
	}  
	static CSingleton *m_pInstance;  
	class CGarbo   //它的唯一工作就是在析构函数中删除CSingleton的实例  
	{  
	public:  
		~CGarbo()  
		{  
			printf("delete");
			if(CSingleton::m_pInstance)  
				delete CSingleton::m_pInstance;  
		}  
	};  
	static CGarbo Garbo;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数
public:  
	static CSingleton * GetInstance()  
	{  
		if(m_pInstance == NULL)  //判断是否第一次调用  
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