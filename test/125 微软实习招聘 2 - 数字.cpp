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

struct Rule {
	string AorD;
	int addr[4];
	int mask;
};

vector<Rule > ruleV;

void strSplit(const string& src, const string& separator, vector<string>& dest)
{
	string str = src;
	string substring;
	string::size_type start = 0, index;

	do
	{
		index = str.find_first_of(separator,start);
		if (index != string::npos)
		{    
			substring = str.substr(start,index-start);
			dest.push_back(substring);
			start = str.find_first_not_of(separator,index);
			if (start == string::npos) return;
		}
	}while(index != string::npos);

	//the last token
	substring = str.substr(start);
	dest.push_back(substring);
}

void splitMask(string &addr,int &mask) {

	vector<string> v;
	strSplit(addr,"/",v);
	
	if(v.size()>1) {
		addr = v[0];
		mask = stringToNum<int >(v[1]);
	}
	else
		mask = -1;
}

//有掩码的情况下，判断是否能
//返回1 代表allow不成功
//返回2 代表allow成功
//返回3 代表deny不成功
//返回4 代表deny成功
int work(int* reqStr,Rule r) {

	int* ruleStr = r.addr;
	int mask = r.mask;

	int maskStrCnt = mask/8; //表示之前多少ip只用比较字符串
	for(int i=0;i<maskStrCnt;++i) {
		
		if(reqStr[i] != ruleStr[i]) {

			//若前面都不相等直接return
			if(r.AorD == "allow") //allow不成功
				return 1;

			else
				return 3;
		}
	}

	//继续比较后面的数
	int maskNumCnt = mask % 8; //接下来需要比较二进制数值大小

	int reqNum = reqStr[maskStrCnt];
	int ruleNum = ruleStr[maskStrCnt];

	int res = reqNum^ruleNum; //异或操作

	if( res >= pow(2,8-maskNumCnt) ) { //在前面不同了
		if(r.AorD == "allow")
			return 1;
		else
			return 3;
	}

	else {
		if(r.AorD == "allow")
			return 2;
		else
			return 4;
	}

}

int main()
{
	freopen("input.txt","r",stdin);

	int N,M;
	cin>>N>>M;

	for(int i=0;i<N;++i) {
		
		Rule tmp;
		memset(tmp.addr,0,sizeof(tmp.addr));
		tmp.mask = -1;
		char tmpC;
		cin>>tmp.AorD;
		cin>>tmp.addr[0];
		cin>>tmpC;
		cin>>tmp.addr[1];
		cin>>tmpC;
		cin>>tmp.addr[2];
		cin>>tmpC;
		cin>>tmp.addr[3];
		tmpC = getchar();

		if(tmpC == '/')
			cin>>tmp.mask;

		ruleV.push_back(tmp);
	}



	//询问
	for(int i=0;i<M;++i) {
		int reqStr[4];
		char tmpC;
		cin>>reqStr[0];
		cin>>tmpC;
		cin>>reqStr[1];
		cin>>tmpC;
		cin>>reqStr[2];
		cin>>tmpC;
		cin>>reqStr[3];

		//挨个检测rule
		int j;
		for(j=0;j<N;++j) {

			if(ruleV[j].mask == -1 || ruleV[j].mask == 32) {
				//没有掩码，直接判断
				if(ruleV[j].addr[0] == reqStr[0] && ruleV[j].addr[1] == reqStr[1]
				&& ruleV[j].addr[2] == reqStr[2] && ruleV[j].addr[3] == reqStr[3]) {
					if( ruleV[j].AorD == "allow" )
						cout<<"YES"<<endl;
					else
						cout<<"NO"<<endl;

					break;
				}
			}

			else { //有掩码

				//特殊判断mask == 0
				if(ruleV[j].mask == 0) {
					if( ruleV[j].AorD == "allow" )
						cout<<"YES"<<endl;
					else
						cout<<"NO"<<endl;

					break;
				}

				//返回1 代表allow不成功
				//返回2 代表allow成功
				//返回3 代表deny不成功
				//返回4 代表deny成功
				int resNum = work(reqStr,ruleV[j]);
				if( resNum == 1 )
					continue;
				else if( resNum == 2 ) {
					cout<<"YES"<<endl;
					break;
				}else if( resNum == 3 ) {
					continue;
				}else if( resNum == 4 ) {
					cout<<"NO"<<endl;
					break;
				}
					
			}

		}

		if( j == N)
			cout<<"YES"<<endl;
	}

	return 0;
}