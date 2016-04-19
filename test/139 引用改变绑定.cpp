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

int main()
{
	//freopen("input.txt","r",stdin);\

	int i=5,j=6;
	int &r = i;
	void *pi = &i,*pj = &j;
	int* addr;
	int dis = (int)pj-(int)pi;
	addr = (int *)((int)pj+dis); //精确计算r的地址

	cout<<"&i == "; PRINT(pi); //i的地址
	cout<<"&j == "; PRINT(pj); //j的地址
	cout<<"&pi == "; PRINT(&pi); //pi的地址
	cout<<"&pj == "; PRINT(&pj); //pj的地址
	cout<<"dis == "; PRINT(dis);
	PRINT(*addr);

	//(*add)+=dis;
	(*addr)=(int)&j; PRINT(*addr); //将r指向j

	r=666;
	cout<<"i == "; PRINT(i);
	cout<<"j == "; PRINT(j);

	return 0;
}