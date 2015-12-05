#include <iostream>
using namespace std;

int main()
{
	int T,hour,minute;
	cin>>T;
	while (T--)
	{
		scanf("%d",&hour);
		getchar();
		scanf("%d",&minute);

		if(minute>0)
		{
			cout<<"0"<<endl;
			continue;
		}

		if(hour<=12)
			cout<<(hour+12)<<endl;

		else
			cout<<(hour-12)<<endl;
	}

	return 0;
}
