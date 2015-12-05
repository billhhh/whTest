#include <iostream>
using namespace std;

int main()
{
	int l,m,start,end;
	while (cin>>l>>m)
	{
		if(0 == l)
			break;

		++l;
		for (int i=0;i<m;++i)
		{
			cin>>start>>end;
			l -= (end-start+1);
		}
		cout<<l<<endl;
	}

	return 0;
}
