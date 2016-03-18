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

const int maxn = 100000 + 5;
int n;

struct Point
{
	int x, y;
	Point (int _x = 0, int _y = 0)
		:x(_x), y(_y) { }
};

map<int, vector<pair<int,int> > > segments[4];

int judgeSegment(const Point & a, const Point & b)
{
	if (a.y == b.y) {
		segments[0][a.y].push_back(make_pair(a.x, b.x));
		return 0;   //水平
	}
	else if (a.x == b.x) {
		segments[1][a.x].push_back(make_pair(a.y, b.y));
		return 1;  //垂直
	}
	else if (a.y < b.y) {
		segments[2][a.y - a.x].push_back(make_pair(a.x, b.x));
		return 2;   //正45
	}
	else {
		segments[3][a.y + a.x].push_back(make_pair(a.x, b.x));
		return 3;  //反45
	}
}

int countSegment(vector<pair<int, int> >  lrPairs)
{
	int res = 0;
	sort(lrPairs.begin(), lrPairs.end());
	int pre = -1e9;
	for (auto lrPair : lrPairs) {
		if (lrPair.first > pre) ++res;
		pre = max(pre, lrPair.second);
	}
	return res;
}


void solve()
{
	int ans = 0;
	for (int i = 0; i < 4; ++i) for (auto & lrPairs : segments[i]) {
		ans += countSegment(lrPairs.second);
	}
	printf("%d\n", ans);
}

int main()
{
	int T; cin >> T;
	while (T--) {

		scanf("%d", &n);
		for (int i = 0; i < 4; ++i) segments[i].clear();
		for (int i = 0; i < n; ++i) {
			Point a, b;
			scanf("%d%d", &a.x, &a.y);
			scanf("%d%d", &b.x, &b.y);
			if (a.x > b.x || (a.x == b.x && a.y > b.y)) swap(a, b);
			judgeSegment(a, b);
		}

		solve();
		puts("");
	}
}