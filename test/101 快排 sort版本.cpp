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

#define MAXN 250002

long long a[MAXN];

int main()
{
	//freopen("input.txt","r",stdin);

	int N;
	cin>>N;

	for (int i = 1; i <= N; ++i) {
		scanf("%lld",&a[i]);
	}

	sort(a+1,a+N+1);

	//odd
	if(N%2)
		printf("%lld.0\n", a[(N+1)/2]);
	else {
		//printf("%.1lf\n", ((double)a[N/2]+(double)a[(N/2)+1])/2); //ok

		//ok
// 		double sum = (double)a[N/2]+(double)a[(N/2)+1];
// 		printf("%.1lf\n",sum / 2);

		printf("%.1lf\n", (double)(a[N/2]+a[(N/2)+1])/2);
	}

	return 0;
}