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

#define MAXN 1002
int dp[MAXN];
int num[MAXN];

int whMaxSub(int a[],int len) {

	dp[0] = a[0];
	for (int i=1;i<len;++i) {

		if(dp[i]<0)
			dp[i] = a[i];
		else
			dp[i] = max(dp[i-1],dp[i-1]+a[i]);
	}

	return dp[len-1];
}

int main()
{
	freopen("input.txt","r",stdin);

	//输入
	int cnt = 0;
	while (cin>>num[cnt++]);
	--cnt; //真实个数

	whMaxSub(num,cnt);

	return 0;
}