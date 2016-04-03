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

struct tmp {
	int aa;
	char bb;
	double cc;
};

struct TStruct
{
	char c;
	double b;
	int a;
	tmp ss;
};

int main()
{
	cout << sizeof(tmp) << endl;
	cout << sizeof(TStruct) << endl;

	return 0;
}