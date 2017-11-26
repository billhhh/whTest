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

int graph_map[8][8];
int visit[8];
int inStack[8];
int loop_cnt = 0;

void DFS(int node) {

	stack<int > s;
	
	//init
	s.push(node);
	inStack[node] = 1;
	while (!s.empty()) {
		int process_node = s.top();
		s.pop();
		inStack[process_node] = 0;
		visit[process_node] = 1;

		//push the children of process_node into s
		for (int i = 1; i <= 7; i++) {
			if (graph_map[process_node][i] == 1 && !visit[i]) {
				//if in the stack already, so there is a loop
				if (inStack[i])
					loop_cnt++;

				//or push it into the stack
				s.push(i);
				inStack[i] = 1;

			}
		}

	}
}

int main()
{
	//freopen("input.txt","r",stdin);
	graph_map[1][2] = 1;
	graph_map[2][1] = 1;

	graph_map[1][3] = 1;
	graph_map[3][1] = 1;

	graph_map[2][4] = 1;
	graph_map[4][2] = 1;

	graph_map[2][5] = 1;
	graph_map[5][2] = 1;

	graph_map[5][6] = 1;
	graph_map[6][5] = 1;

	graph_map[6][7] = 1;
	graph_map[7][6] = 1;

	graph_map[5][7] = 1;
	graph_map[7][5] = 1;

	graph_map[5][3] = 1;
	graph_map[3][5] = 1;

	graph_map[2][3] = 1;
	graph_map[3][2] = 1;

	DFS(1);

	cout << loop_cnt << endl;

	return 0;
}