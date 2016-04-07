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
	string addr;
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

//�����������£��ж��Ƿ���
//����1 ����allow���ɹ�
//����2 ����allow�ɹ�
//����3 ����deny���ɹ�
//����4 ����deny�ɹ�
int work(string reqStr,Rule r) {

	string ruleStr = r.addr;
	int mask = r.mask;

	vector<string> reqV;
	vector<string> ruleV;

	strSplit(reqStr,".",reqV);
	strSplit(ruleStr,".",ruleV);

	int maskStrCnt = mask/8; //��ʾ֮ǰ����ipֻ�ñȽ��ַ���
	for(int i=0;i<maskStrCnt;++i) {
		
		if(reqV[i] != ruleV[i]) {

			//��ǰ�涼�����ֱ��return
			if(r.AorD == "allow") //allow���ɹ�
				return 1;

			else
				return 3;
		}
	}

	//�����ȽϺ������
	int maskNumCnt = mask % 8; //��������Ҫ�Ƚ϶�������ֵ��С

	int reqNum = stringToNum<int>(reqV[maskStrCnt]);
	int ruleNum = stringToNum<int>(ruleV[maskStrCnt]);

	int res = reqNum^ruleNum; //������

	if( res >= pow(2,8-maskNumCnt) ) { //��ǰ�治ͬ��
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
	//freopen("input.txt","r",stdin);

	int N,M;
	cin>>N>>M;

	for(int i=0;i<N;++i) {
		
		Rule tmp;
		cin>>tmp.AorD>>tmp.addr;

		//��addr��
		splitMask(tmp.addr,tmp.mask);

		ruleV.push_back(tmp);
	}



	//ѯ��
	for(int i=0;i<M;++i) {
		string reqStr;
		cin>>reqStr;

		//�������rule
		int j;
		for(j=0;j<N;++j) {

			if(ruleV[j].mask == -1 || ruleV[j].mask == 32) {
				//û�����룬ֱ���ж�
				if(ruleV[j].addr == reqStr) {
					if( ruleV[j].AorD == "allow" )
						cout<<"YES"<<endl;
					else
						cout<<"NO"<<endl;

					break;
				}
			}

			else { //������

				//�����ж�mask == 0
				if(ruleV[j].mask == 0) {
					if( ruleV[j].AorD == "allow" )
						cout<<"YES"<<endl;
					else
						cout<<"NO"<<endl;

					break;
				}

				//����1 ����allow���ɹ�
				//����2 ����allow�ɹ�
				//����3 ����deny���ɹ�
				//����4 ����deny�ɹ�
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