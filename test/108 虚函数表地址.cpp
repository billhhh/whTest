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

class Base {
public:
	virtual void f() { cout << "Base::f" << endl; }
	virtual void g() { cout << "Base::g" << endl; }
};

class Derive:public Base
{
public:
	void f(){ cout << "Derive::f" << endl; }
	virtual void f1() { cout << "Derive::f1" << endl; }

};

int main()
{
	//freopen("input.txt","r",stdin);

	typedef void(*Fun)(void);

// 	Base b;
// 	Fun bFun = (Fun)*((int*)*(int*)(&b));
// 	bFun();
// 	bFun = (Fun)*((int*)*(int*)(&b)+1);
// 	bFun();
// 	cout<<bFun<<endl;

	Derive d;
	Fun dFun = (Fun)*((int*)*(int*)(&d));
// 	dFun();
// 	dFun = (Fun)*((int*)*(int*)(&d)+1);
// 	dFun();
// 	dFun = (Fun)*((int*)*(int*)(&d)+2);
// 	dFun();
 	cout<<dFun<<endl;

	Derive d2;
	Fun dFun2 = (Fun)*((int*)*(int*)(&d2));
	cout<<dFun2<<endl;

	return 0;
}
