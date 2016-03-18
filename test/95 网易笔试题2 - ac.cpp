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

using namespace std;

const int MAXN = 1002;
int n;
vector<int> G[MAXN];
int dependFileCnt[MAXN];
map<string, int> id;
string cppName[MAXN];

struct node
{
	int id;
	node(int _id)
		: id(_id) { }
	friend bool operator < (const node & n1, const node & n2)
	{
		return cppName[n1.id] > cppName[n2.id];
	}
};

int main()
{
	int T;
	cin >> T;

	while (T--) {
		//init
		memset(dependFileCnt, 0, sizeof(dependFileCnt));
		for (int i = 0; i < MAXN; ++i) {
			G[i].clear();
		}
		id.clear();
		scanf("%d", &n);
		for (int u = 0; u < n; ++u) {
			cin >> cppName[u];
			id[cppName[u]] = u;

			int m;
			scanf("%d", &m);
			while (m--) {
				int v;
				scanf("%d", &v);
				G[v].push_back(u);
				++dependFileCnt[u];
			}
		}

		priority_queue<node> q;
		for (int i = 0; i < n; ++i) if (!dependFileCnt[i]) {
			q.push(node(i));
		}

		vector<int> res;
		while (!q.empty()) {
			int u = q.top().id;
			q.pop();

			res.push_back(u);

			for (int i = 0; i < G[u].size(); ++i) {
				int v = G[u][i];
				if (--dependFileCnt[v] == 0) q.push(node(v));
			}
		}

		if (res.size() != n) {
			puts("ERROR");
		} else {
			for (int i = 0; i < res.size(); ++i) {
				printf("%s\n", cppName[res[i]].c_str());
			}
		}

		puts("");
	}
}
