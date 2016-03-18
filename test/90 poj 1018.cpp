#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
const int Max=101;

struct node //ÿ�Գ��̸�������
{
	double b;
	double p;
};

node a[Max][Max];
double b[Max*Max]; //b���⿪�ٵ�����
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

		//��������
		for (i=0;i<n;i++)
		{
			cin>>m[i];
			for (j=0;j<m[i];j++)
			{
				cin>>a[i][j].b>>a[i][j].p;
				b[bsize++]=a[i][j].b;
			}
		}
		qsort(b,bsize,sizeof(b[0]),cmp); //����b���򣬷���ö��

		double mmax=0;
		double mmin;
		double sump=0;
		double temp=0;
		for (i=0;i<=bsize-1;i++)
		{
			//����С����ʼö�٣���̰�ķ�ѡ��������ڵ�����С�������ͼ۸�
			//Ȼ���ٱȽϸ�������(B/P)��ֵ��ֱ������������
			//����Ӵ���ö����ȥ��һ������Ҫ��
			sump=0;
			int changFlag = 0; //��֦
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