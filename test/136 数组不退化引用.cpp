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

void func(int (&b) [20][10]) {
	PRINT(b[20][1000]);
}

void func(int *b) {

}

void func2(int a[5]) {
	PRINT(sizeof(a));
	PRINT(a[3]);
	PRINT(a[10]);
}

// int&[20] func3() {
// 
// 	int arr[20];
// 	return arr;
// }

int main()
{
	//freopen("input.txt","r",stdin);

	int a[20][10];

	a[2][1] = 5;

	a[22][12] = 5;
	cout<<a[22][12]<<endl;

	func(a);

	int b[4];
	b[3] = 666;
	func2(b);

	return 0;
}