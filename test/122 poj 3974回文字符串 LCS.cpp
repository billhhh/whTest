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

#define MAXN 1000002
char s[MAXN];

int dp[2][MAXN];

int whLCS() {
	memset(dp,0,sizeof(dp));
	int len = strlen(s);

	int i;
	for(i=1;i<=len;++i) {

		for (int j=1;j<=len;++j) {

			if( s[i-1] == s[len-j] )
				dp[i%2][j] = dp[(i-1)%2][j-1]+1;
			else
				dp[i%2][j] = max(dp[(i-1)%2][j],dp[i%2][j-1]);
		}
	}

	//return dp[(i-1)%2][len];

	int cnt = 0;
	int row = (i-1)%2; //½á¹ûÐÐ
	int resMax = 0;
	for (int j=1;j<=len;++j) {

		if(dp[row][j] != dp[row][j-1])
			cnt++;
		else{
			resMax = max(resMax,cnt);
			cnt = 0;
		}
	}
	resMax = max(resMax,cnt);
	return resMax;
}

int main()
{
	//freopen("input.txt","r",stdin);

	int T = 1;
	while (cin>>s) {

		if(strcmp(s,"END")==0)
			break;

		int res = whLCS();
		cout<<"Case "<<T<<": ";
		PRINT(res);
	}

	return 0;
}