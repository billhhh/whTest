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
#include <list>
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

#define MAXN 250002

vector<int > v;

//有序数组递减排列
int  binarySearch(vector<int > array,int len,int value){
	int mid=0;
	int low=0;
	int high=len-1;
	while(low<=high){
		mid=(low+high)/2;
		if(array[mid]>value){       //在右半区
			low=mid+1;
			continue;
		}
		else if(array[mid]<value){  //在左半区
			high=mid-1;
			continue;
		}else
			return mid;             //找到
	}
	return low;  //insert pos
}

int main()
{
	//freopen("input.txt","r",stdin);

	int N;
	cin>>N;

	for (int i = 1; i <= N; ++i) {
		long long tmp;
		scanf("%lld",&tmp);

		int pos = binarySearch(v,i-1,tmp);
		v.insert(v.begin() + pos, tmp);
	}


	if(N%2) //odd
		printf("%lld.0\n", v[(N+1)/2-1]);
	else
		printf("%.1lf\n", (double)(v[N/2-1]+v[N/2])/2);

	return 0;
}