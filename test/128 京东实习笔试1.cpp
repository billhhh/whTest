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

#define MAXN 100002

int d[N],w[N];

int dp[]

void knapsack()
{
	int i,j;
	memset(val,0,sizeof(val));
	for(i=1;i<=n;i++)
		for(j=W;j>=1;j--)
		{//��ǰ���������ȵ�i����Ʒ������ҵ�ǰ��ֵ�ȸ��º��ֵС�������
			if(j>=w[i]&&val[j-w[i]]+d[i]>val[j])
				val[j]=val[j-w[i]]+d[i];
		}
		return ;
}

int main()
{
	freopen("input.txt","r",stdin);

	int n; //�ɹ�ѡ���ǹ�����
	long long v; //����������

	for (int i=0;i<n;++i) {

	}

	return 0;
}