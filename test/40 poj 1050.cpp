#include <iostream>
using namespace std;

#define MAXN 102

int map[MAXN][MAXN];
int colsum[MAXN][MAXN];

int main()
{
	int n;
	cin>>n;

	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)
		{
			cin>>map[i][j];
			colsum[i][j+1]=colsum[i][j]+map[i][j];
		}

	int max = 0;
	for (int i=0;i<n;++i)
	{
		for (int j=i;j<=n;++j) //从第i行到第j行
		{
			int sum=0;
			for (int k=0;k<n;++k) //每列的和
			{
				sum+=colsum[k][j]-colsum[k][i];
				sum = sum<0?0:sum;
				max = sum>max?sum:max;
			}
		}
	}
	
	cout<<max<<endl;
	return 0;
}
