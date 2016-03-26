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

class whString
{
public:
	whString& operator = (const whString &str);

	whString () {m_pData = NULL;};

	whString(const char *s) {
		m_pData = new char[strlen(s) + 1];
		strcpy(m_pData,s);
	}

	~whString() {
		delete []m_pData;
		m_pData = NULL;
	}

	void stringPrint() {
		cout<<m_pData<<endl;
	}
private:
	char *m_pData;
};

whString& whString::operator = (const whString &str) {

	cout<<"enter whString::operator =()"<<endl;

	if( &str != this ) {
		whString strTmp(str);

		char* pTmp = strTmp.m_pData;
		strTmp.m_pData = m_pData; //自动调用析构
		m_pData = pTmp;
	}
	
	return *this;
}

int main()
{
	//freopen("input.txt","r",stdin);

	whString a = "abc";

	whString b;
	b = a;
	b.stringPrint();

	return 0;
}