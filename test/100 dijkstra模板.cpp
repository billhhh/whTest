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
bool visited[MAXN];

void update(int minPos,int n) {

	for (int i = 1; i <= n; ++i) {

		if( !visited[i] && map[1][i] > map[1][minPos] + map[minPos][i] )
			map[i][1] = map[1][i] = map[1][minPos] + map[minPos][i];
	}
}

void dijkstra(int n) {

	visited[1] = 1;
	while(1) {

		int tmpMin = INF;
		int minPos = -1;
		for (int i = 2; i <= n; ++i) {

			if( !visited[i] && tmpMin > map[1][i] ) {
				//have not been visited && smaller

				tmpMin = map[1][i];
				minPos = i;
			}
		}

		if( -1 == minPos )
			break;

		visited[minPos] = 1;
		update(minPos,n); //update the map, if it's shorter to get through minPos
	}
}

int main()
{
	//freopen("input.txt","r",stdin);

	int n=4;
	map[1][2]=map[2][1]=10;  
	map[1][3]=map[3][1]=4;  
	map[2][3]=map[3][2]=5;  
	map[2][4]=map[4][2]=2;  
	map[4][3]=map[3][4]=1;

	dijkstra(n);

	for (int i = 2; i <= n ; ++i) {
		cout<<map[1][i]<<endl;
	}

	return 0;
}