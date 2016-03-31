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

int main()
{
	//freopen("input.txt","r",stdin);
	int a = 1;
	int b = 2;
	int pa = (int)&a;
	int pb = (int)&b;

// 	cout<<pa<<endl;
// 
// 	cout<<*((int)pa+pb)<<endl;
// 	a = a^b;
// 	b = a^b;
// 	a = a^b;

// 	pa = pa^pb;
// 	pb = pa^pb;
// 	pa = pa^pb;

// 	long long sum = pa + pb;
// 	pb = sum - pb;
// 	pa = sum - pa;

	pa = pa + pb;
	pb = pa - pb;
	pa = pa - pb;

	cout<<*(int *)pa<<endl;
	cout<<*(int *)pb<<endl;

	return 0;
}