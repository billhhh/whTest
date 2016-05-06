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

int Max(const int &a,const int &b) {
	return (a>b)?a:b;
}

int main()
{
	//freopen("input.txt","r",stdin);

	char c='a';
	const int &rc = c;
	PRINT(c);
	PRINT(rc);
	PRINT((void*)&c);
	PRINT((void*)&rc);

	int dis = (int)&rc-(int)&c;
	PRINT(dis);
	int* addr = (int*)((int)&c+dis); //精确计算rc指向的无名变量的地址

	*addr = 666;
	PRINT(c);
	PRINT(rc);

	return 0;
}