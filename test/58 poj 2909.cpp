#include <iostream>
#define MAXN 1<<15

using namespace std;

int prime[MAXN];

//为0代表是素数
int findPrime()
{
	//先打出素数表
	prime[0]=prime[1]=1;
	int i,j;
	for(i=2;i<MAXN;i++)
	{
		if(prime[i]==0)
		{
			for(j=2*i;j<MAXN;j+=i)
				prime[j]=1;
		}
	}

	return 0;
}

int main() {

	//freopen("input.txt","r",stdin);

	findPrime();

	int n;
	while ( cin>>n ,n ) {
		int count = 0;
		for(int i=2;i<=n/2;++i) {
			if( !prime[i] && !prime[n-i] )
				count++;
		}
		cout<<count<<endl;
	}

	return 0;
}
