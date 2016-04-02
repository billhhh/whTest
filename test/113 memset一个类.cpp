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

class CTest
{
public:
	int a;
	CTest() {memset(this,0,sizeof(*this)); }
	void printSize() {cout<<sizeof(*this)<<endl;}
};

int main()
{
	//freopen("input.txt","r",stdin);

	CTest t;
	//t.printSize();

	return 0;
}