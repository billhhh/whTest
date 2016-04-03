//Memory Time 
//280K  1157MS 

#include<iostream>
using namespace std;

int max(int a,int b)
{
	return a>b?a:b;
}

int main(int i,int j)
{
	int n;
	while(cin>>n)
	{
		/*Input*/

		char* s1=new char[n+1];
		char* s2=new char[n+1];   //s1的逆序列

		int **dp=new int*[n+1];   //定义二维动态滚动数组（本题以01行滚动）
		dp[0]=new int[n+1];
		dp[1]=new int[n+1];
		dp[0][0]=dp[1][0]=0; //动态数组初始化 行开头为全0

		for(i=1,j=n;i<=n;i++,j--)
		{
			dp[0][i]=dp[1][i]=0;  //动态数组初始化 列开头为全0

			char temp;
			cin>>temp;
			s1[i]=s2[j]=temp;
		}

		/*Dp-LCS*/

		int max_len=0;
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
			{
				if(s1[i]==s2[j])
					dp[i%2][j]=dp[(i-1)%2][j-1]+1;   //如果字符相等，则继承前一行前一列的dp值+1
				else
					dp[i%2][j]=max(dp[(i-1)%2][j],dp[i%2][j-1]); //否则，取上方或左方的最大dp值

				if(max_len<dp[i%2][j])
					max_len=dp[i%2][j];
			}

			cout<<n-max_len<<endl;

			delete s1;
			delete s2;
			delete[] dp;
	}
	return 0;
}