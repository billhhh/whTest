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

#define MAXN 205

int dp[MAXN][MAXN];

int whLCS(char s1[],int len1,char s2[],int len2) {

	for(int i=1;i<=len1;++i) {

		for (int j=1;j<=len2;++j) {

			if(s1[i-1]==s2[j-1])
				dp[i][j]=dp[i-1][j-1]+1;
			else
				dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
		}
	}
	return dp[len1][len2];
}

int main()
{
	freopen("input.txt","r",stdin);

	char s1[MAXN],s2[MAXN];

	while (scanf("%s %s",s1,s2)!=EOF) {
		
		int res = whLCS(s1,strlen(s1),s2,strlen(s2));
		PRINT(res);
	}

	return 0;
}