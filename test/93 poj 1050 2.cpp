#include<stdio.h>

#define N 103

//����Ӷκ�
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

	//��������
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			scanf("%d",&map[i][j]);

	max=0;
	for(i=1;i<=n;i++) //ÿһ��
	{
		for(j=1;j<=n;j++)
			dp[j]=0; //��ʼ��

		for(j=i;j<=n;j++) //j����i���������
		{
			for(k=1;k<=n;k++) //k������
				dp[k]+=map[j][k]; //��һ���Ӷκ��ۼ�����һ��

			sum=fun(dp,n);

			if(max<sum)
				max=sum;
		}

	}
	printf("%d\n",max);
	return 0;
}