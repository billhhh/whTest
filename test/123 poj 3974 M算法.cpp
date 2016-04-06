//Memory: 43376K		Time: 844MS

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

#define MAXN 10000002

int P[MAXN];
char s[2*MAXN+2];

int Manacher(string tmp) {

	memset(P,0,sizeof(P));

	int len=tmp.size();
	
	int k;
	for(k=0;k<len;k++){
		s[2*k] = '#';
		s[2*k+1] = tmp[k];
	}
	s[2*k] = '#';
	s[2*k+1] = '\0';

	//算法核心
	len=strlen(s);
	int mx = 0; //mx 记在i之前的回文串中，延伸至最右端的位置
	int id=0; //id 记下取得这个最优mx时的 坐标值
	for (int i=0;i<len;++i) {

		if( i < mx ) //在当前最优边界左边
			P[i] = min(P[2*id-i],mx-i);
		else
			P[i]=1;

		for (;s[i-P[i]] == s[i+P[i]] && s[i-P[i]] != '\0' && s[i+P[i]] != '\0' ; ) //对于超出mx或者P[j]边界的计算
			P[i]++;

		if( P[i]+i > mx ) { //当前最佳情况，update mx和id
			mx = P[i] + i; //最右端情况
			id = i; //记下坐标
		}
	}

	int res = 0;
	for (int i=0;i<len;++i) {
		res = max(res,P[i]);
	}

	return res-1;
}

int main()
{
	//freopen("input.txt","r",stdin);

	string tmp;
	int T=0,res;
	while(cin>>tmp){

		if("END"==tmp)
			break;

		cout<<"Case "<<++T<<": ";

		int res = Manacher(tmp);

		PRINT(res);
	}

	return 0;
}
