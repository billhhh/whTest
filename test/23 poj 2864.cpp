#include <iostream>
#include <string>
using namespace std;

int flag[102];

int main()
{
	int N,D,i;
	int tmp;
	while (cin>>N>>D)
	{
		if(0 == N && 0== D)
			break;

		memset(flag,0,sizeof(flag));
		for(i=0;i<D;++i)
			for(int j=0;j<N;++j)
			{
				cin>>tmp;
				if(0 == tmp)
					flag[j]=1;
			}

			for (i=0;i<N;++i)
			{
				if(0 == flag[i])
				{
					cout<<"yes"<<endl;
					break;
				}
			}
			if(i==N)
				cout<<"no"<<endl;
	}

	return 0;
}
