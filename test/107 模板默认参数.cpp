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

template<class T1,class T2,class T3>
T1 sum(T1 a,T2 b,T3 c){
	return a+b+c;
} 

void main(){
	//cout<<sum<double,double>(1.1,2.1,3)<<endl;
	char a = -128;
	//cout<<a-1<<endl;
	printf("%d\n",--a);
}