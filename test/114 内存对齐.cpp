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

struct TStruct
{
	int a;
	char b;
	double c;
};

int main()
{
	//freopen("input.txt","r",stdin);

// 	TStruct t;
// 	cout<<sizeof(t)<<endl;

// 	int a[100];
// 	cout<<a<<endl;
// 	cout<<a+3<<endl;

	int a;
	int b;

	cout<<&a<<endl;
	cout<<&b<<endl;

	return 0;
}