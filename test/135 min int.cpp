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
	//freopen("input.txt","r",stdin);

	int a = INF;

	int maxInt = 0x7fffffff; //最大int

	int minusOne = 0xffffffff; //-1s
	int minInt = 0x80000000; //最小int

	int minusMaxInt = 0x80000001; //-maxInt

	return 0;
}