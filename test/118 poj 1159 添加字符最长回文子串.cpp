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

#define MAXN 5002

int dp[2][MAXN]; //а╫ее

int whLCS(char s1[],int len1,char s2[],int len2) {
	
	int rowFlag = 1;
	for(int i=1;i<=len1;++i) {

		for (int j=1;j<=len2;++j) {

			if(s1[i-1]==s2[j-1])
				//dp[i][j]=dp[i-1][j-1]+1;
				dp[rowFlag][j]=dp[!rowFlag][j-1]+1;
			else
				dp[rowFlag][j]=max(dp[!rowFlag][j],dp[rowFlag][j-1]);
		}
		rowFlag = !rowFlag;
	}
	return dp[!rowFlag][len2];
}

int main()
{
	//freopen("input.txt","r",stdin);

	int n;
	cin>>n;

	char input[MAXN];
	char reverse[MAXN];

	getchar();
	int i;
	for (i=0;i<n;++i){
		cin>>input[i];
		reverse[n-1-i]=input[i];
	}
	input[i]='\0';
	reverse[i]='\0';

	int res = whLCS(input,strlen(input),reverse,strlen(reverse));

	cout<<strlen(input) - res<<endl;

	return 0;
}