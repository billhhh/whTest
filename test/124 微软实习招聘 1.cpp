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
#define  MAXN 1002

int a[MAXN]; //每个段落字数

inline int upperCnt(int s,int t) {
	return s%t == 0?(s/t):(s/t+1);
}

int main()
{
	//freopen("input.txt","r",stdin);

	int T;
	cin>>T;

	while (T--) {

		int N,P,W,H;
		cin>>N>>P>>W>>H;

		for (int i=0;i<N;++i)
			cin>>a[i];

		//start
		//枚举S
		int S;
		for(S=1;W>=S && H>=S;++S){
			int pageCnt = 0;
			int rowCapacity = H/S; //行容量
			int curRow = 0;
			for(int j=0;j<N;++j) {
				curRow += upperCnt(a[j],W/S); //算出一个段落多少行

				while(curRow>=rowCapacity) {
					curRow -= rowCapacity;
					pageCnt++;
				}
			}
			if(pageCnt>P)
				break;
		}

		PRINT(S-1);
	}

	return 0;
}