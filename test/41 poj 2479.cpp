#include <iostream>
#include <limits>
using namespace std;

#define MAXN 50002
int map[MAXN];
int Ldp[MAXN];
int Rdp[MAXN];

void MaxLSub (int a[],int N)//此为只需要求最大的和，时间复杂度是O(n)  
{
	int i;

	Ldp[0] = a[0];
	for (i=1; i<N; i++)
	{
		if (Ldp[i-1] > 0)
			Ldp[i] = Ldp[i-1] + a[i];
		else
			Ldp[i] = a[i];
	}

	for(i=1; i<N; i++)
		Ldp[i] = Ldp[i]<Ldp[i-1]?Ldp[i-1]:Ldp[i];
}

void MaxRSub (int a[],int N)//此为只需要求最大的和，时间复杂度是O(n)  
{
	int i;

	Rdp[N-1] = a[N-1];
	for (i=N-2; i>-1; i--)
	{
		if(Rdp[i+1]>0)
			Rdp[i] = Rdp[i+1]+a[i];
		else
			Rdp[i] = a[i];
	}

	for (i=N-2; i>-1; i--)
		Rdp[i] = Rdp[i]<Rdp[i+1]?Rdp[i+1]:Rdp[i];
}

int main()
{
	int T,n;
	cin>>T;

	while (T--)
	{
		//scanf("%d",&n);
		cin>>n;
		for (int i=0;i<n;++i)
		{
			//scanf("%d",&map[i]);
			cin>>map[i];
		}

		MaxLSub(map,n); //生成dp
		MaxRSub(map,n);

		int res=INT_MIN;
		for (int i=1;i<=n-1;++i)
		{
			int tmp = Ldp[i-1]+Rdp[i];
			res = tmp>res?tmp:res;
		}
		
		cout<<res<<endl;
	}

	return 0;
}
