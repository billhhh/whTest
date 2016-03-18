/* 
* 
* function: poj 1050 dp
* 
* Date:2016-3-18
* 
*    Author: Bill Wang
*/

#include <iostream>
using namespace std;

#define MAXN 102
#define MAP_MIN -1000

int map[MAXN][MAXN];
int dp[MAXN][MAXN];

//计算出(ax,ay)到(bx,by)下所有方块的和
int whSum(int ax,int ay, int bx, int by) {
	
	int res = 0;

	for (int i=ax;i<=bx;++i) {

		for(int j=ay;j<=by;++j) {
			res += map[i][j];
		}
	}

	return res;
}

int whMax(int a,int b,int c,int d) {

	int res = a>b?a:b;
	res = res>c?res:c;
	res = res>d?res:d;

	return res;
}

int main() 
{
	int n;
	cin>>n;

	//dp[i][j] 表示 第i行 第j列最大的值
	for(int i=0;i<MAXN;++i) {
		for(int j=0;j<MAXN;++j) {
			dp[i][j] = MAP_MIN; //初始化
		}
	}

	for (int i=1;i<=n;++i) {
		for (int j=1;j<=n;++j) {
			cin>>map[i][j];
			dp[i][j] = map[i][j];

			dp[i][j] = whMax(dp[i][j]
			,dp[i-1][j-1]+whSum(i,0,i,j-1)+whSum(0,j,i-1,j)+map[i][j]
			,dp[i-1][j]+whSum(i,0,i,j-1)
			,dp[i][j-1]+whSum(0,j,i-1,j));
		}
	}

	cout<<dp[n][n]<<endl;

	return 0; 
}