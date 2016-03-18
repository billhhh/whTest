#include<stdio.h>

#define N 103

//最大子段和
int fun(int dp[N],int n)
{
	int i,max,c;

	c=0;
	max=0;
	for(i=1;i<=n;i++)
	{
		if(c>0)
			c=c+dp[i];
		else c=dp[i];

		if( max<c )
			max = c;
	}
	return max;
}

int main()
{
	int i,j,n,max,sum,k;
	int map[N][N],dp[N];

	//输入数据
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			scanf("%d",&map[i][j]);

	max=0;
	for(i=1;i<=n;i++) //每一行
	{
		for(j=1;j<=n;j++)
			dp[j]=0; //初始化

		for(j=i;j<=n;j++) //j代表i下面的行数
		{
			for(k=1;k<=n;k++) //k代表列
				dp[k]+=map[j][k]; //上一行子段和累加上下一行

			sum=fun(dp,n);

			if(max<sum)
				max=sum;
		}

	}
	printf("%d\n",max);
	return 0;
}