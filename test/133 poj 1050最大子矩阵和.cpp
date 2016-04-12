#include <stdio.h>
#include <stdlib.h>

int m[101][101];

int main()
{
	freopen("input.txt","r",stdin);
    int n,max,i,j,k,tmp;

    while(scanf("%d",&n) != EOF)
    {
        for(i=0;i<n;++i)
        {
            for(j=0;j<n;++j)
                scanf("%d",&m[i][j]);
        }

		max=-10000;
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