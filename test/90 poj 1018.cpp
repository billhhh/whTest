#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
const int Max=101;

struct node //每对厂商给出数据
{
	double b;
	double p;
};

node a[Max][Max];
double b[Max*Max]; //b另外开辟的数组
int m[Max];
int bsize;

int cmp(const void *a,const void *b)
{
	return (*(double *)a)-(*(double *)b);
}

int main()
{
	int t,n;
	cin>>t;
	while (t--)
	{
		memset(a,0,sizeof(a));
		memset(m,0,sizeof(m));
		cin>>n;
		int i,j,k;
		int bsize=0;

		//输入数据
		for (i=0;i<n;i++)
		{
			cin>>m[i];
			for (j=0;j<m[i];j++)
			{
				cin>>a[i][j].b>>a[i][j].p;
				b[bsize++]=a[i][j].b;
			}
		}
		qsort(b,bsize,sizeof(b[0]),cmp); //带宽b排序，方便枚举

		double mmax=0;
		double mmin;
		double sump=0;
		double temp=0;
		for (i=0;i<=bsize-1;i++)
		{
			//从最小带宽开始枚举，用贪心法选出带宽大于等于最小带宽的最低价格
			//然后再比较更新最大的(B/P)的值，直到到达最大带宽
			//如果从带宽枚举上去，一定符合要求
			sump=0;
			int changFlag = 0; //剪枝
			for (j=0;j<n;j++)
			{
				mmin=32767;
				for (k=0;k<m[j];k++)
				{
					if (a[j][k].b>=b[i]&&a[j][k].p<mmin)
					{
						mmin=a[j][k].p;
						changFlag = 1;
					}
				}
				sump+=mmin;
			}
			if(!changFlag)
				break;

			temp=b[i]*1.0/sump;
			if(temp>mmax)
				mmax=temp;
		}
		printf("%.3lf\n",mmax);

	}
	return 0;
}