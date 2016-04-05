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

#define MAXN 10000005

int P[MAXN];

int Manacher(string tmp) {

	memset(P,0,sizeof(P));

	string s;
	int len=tmp.size();
	s="";
	
	for(int i=0;i<len;i++){
		s+="#";s+=tmp[i];
	}
	s+='#';

	//Ëã·¨ºËÐÄ
	len=len*2+1;
	int mx = 0;
	int id=0;
	for (int i=1;i<len;++i) {
		if( mx>i )
			P[i] = min(P[2*id-i],mx-i);
		else
			P[i]=1;
		for (;s[i+P[i]] == s[i-P[i]];P[i]++);

		if( P[i]+i > mx ) {
			mx = P[i] + i;
			id = i;
		}
	}

	return ;
}

int main()
{
	freopen("input.txt","r",stdin);

	string tmp;
	int T=0,res;
	while(cin>>tmp){

		if("END"==tmp)
			break;

		cout<<"Case "<<++T<<": ";

		int res = Manacher(tmp);
	}

	return 0;
}
