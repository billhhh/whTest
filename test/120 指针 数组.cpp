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

void Test(int *pc,int arrc[]) {
	PRINT(sizeof(pc));
	PRINT(sizeof(arrc));

	PRINT(&pc);
	PRINT(&arrc);

	PRINT(&pc+1);
	PRINT(&arrc+1);
}

int main()
{
	//freopen("input.txt","r",stdin);

	int test[10];
	int a[1];
	int b;
	//Test(test,test);

	PRINT(sizeof(test));

	return 0;
}