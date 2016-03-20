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
//#include <map>
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

#define MAXN 102
int map[MAXN][MAXN];

int main()
{
	//freopen("input.txt","r",stdin);

	int n;
	cin >> n;
	for (int i = 2; i <= n; ++i) {
		for (int j = 1; j < i; ++j) {

			string s;
			cin>>s;

			int tmp = INF;
			if(s != "x"){
				tmp = stringToNum<int > (s);
			}

			map[j][i] = map[i][j] = tmp;
		}
	}

	//floyd
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j < i; ++j) {

				map[j][i] = map[i][j] = min(map[i][j],map[i][k]+map[k][j]);
			}
		}
	}

	int time = -1;
	for (int i = 2; i <= n ; ++i) {
		time = time > map[1][i]? time : map[1][i];
	}
	cout<<time<<endl;

	return 0;
}