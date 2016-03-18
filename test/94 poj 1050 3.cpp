#include <stdio.h>
#include <stdlib.h>

int m[101][101];

int main()
{
	int n,max,i,j,k,tmp;

	while(scanf("%d",&n) != EOF)
	{
		max=-10000;
		/*
		输入时，顺便求出各行的最大字段和的最大值
		*/
		for(i=0;i<n;++i)
		{
			tmp=0;
			for(j=0;j<n;++j)
			{
				scanf("%d",&m[i][j]);
				if(tmp>0)tmp+=m[i][j];
				else tmp=m[i][j];

				if(tmp>max)max=tmp;
			}
		}

		for(i=0;i<n-1;++i)
		{
			for(j=i+1;j<n;++j)
			{
				tmp=0;
				for(k=0;k<n;++k)
				{
					//相当于把子矩阵多行压缩为一行了
					m[i][k]+=m[j][k];
					if(tmp>0)tmp+=m[i][k];
					else tmp=m[i][k];

					if(tmp>max)max=tmp;
				}
			}

		}
		printf("%d\n",max);
	}

	return 0;   
}